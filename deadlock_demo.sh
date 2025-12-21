#!/bin/bash

# Deadlock Demonstration Script for philo program
# This script demonstrates mutex deadlock when SIGINT is sent

# set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
PHILO_PROGRAM="./philo"
TIMEOUT=30
TEST_CASES=(
    # "philosophers time_to_die time_to_eat time_to_sleep [meals]"
    "5 800 200 200"      # Classic case - high deadlock potential
    "4 310 200 100 5"      # Small numbers, tight timing
    "6 500 150 150 2"      # Even number, medium timing
    "7 400 200 200 4"      # Odd number, creates imbalance
)

# Log file for debugging
LOG_FILE="deadlock_test_$(date +%Y%m%d_%H%M%S).log"

echo -e "${BLUE}=== Philosopher Deadlock Demonstration ===${NC}"
echo "Log file: $LOG_FILE"
echo "Binary: $PHILO_PROGRAM"
echo ""

# Check if philo program exists
if [ ! -f "$PHILO_PROGRAM" ]; then
    echo -e "${RED}Error: $PHILO_PROGRAM not found${NC}"
    echo "Please run 'make' first to build the program"
    exit 1
fi

# Function to check if process is stuck in deadlock
check_deadlock() {
    local pid=$1
    local start_time=$(date +%s)
    local timeout=10
    
    echo "Monitoring process $pid for deadlock..."
    
    while [ $(($(date +%s) - start_time)) -lt $timeout ]; do
        if ! kill -0 "$pid" 2>/dev/null; then
            echo -e "${GREEN}Process terminated normally${NC}"
            return 1
        fi
        
        # Check if process is in blocked state (common sign of deadlock)
        if command -v ps >/dev/null 2>&1; then
            state=$(ps -o state= -p "$pid" 2>/dev/null | tr -d ' ' || echo "")
            if [ "$state" = "D" ]; then
                echo -e "${RED}Process in uninterruptible sleep (state D)${NC}"
                echo -e "${RED}This indicates probable DEADLOCK!${NC}"
                return 0
            fi
        fi
        
        sleep 1
    done
    
    # Process still running after timeout - likely stuck
    echo -e "${YELLOW}Process still running after $timeout seconds${NC}"
    echo -e "${YELLOW}Likely DEADLOCK or hanging${NC}"
    return 0
}

# Function to run single test case
run_test() {
    local test_params="$1"
    local test_num="$2"
    
    echo -e "\n${BLUE}=== Test Case $test_num: $PHILO_PROGRAM $test_params ===${NC}"
    
    # Start philo program in background
    echo "Starting philo program..."
    $PHILO_PROGRAM $test_params > "test_${test_num}_output.log" 2>&1 &
    local philo_pid=$!
    
    echo "Process ID: $philo_pid"
    
    # Wait for initial setup
    sleep 2
    
    # Check if process is still running
    if ! kill -0 "$philo_pid" 2>/dev/null; then
        echo -e "${RED}Process died before SIGINT could be sent${NC}"
        return 1
    fi
    
    # Send SIGINT to trigger potential deadlock
    echo -e "${YELLOW}Sending SIGINT to process $philo_pid...${NC}"
    kill -INT "$philo_pid" 2>/dev/null || {
        echo -e "${RED}Failed to send SIGINT${NC}"
        return 1
    }
    
    # Immediately check for deadlock
    if check_deadlock "$philo_pid"; then
        echo -e "${RED}✗ DEADLOCK DETECTED!${NC}"
        echo "Process is stuck with locked mutexes"
        
        # Try to get more debug info
        if command -v strace >/dev/null 2>&1; then
            echo "Attempting to trace blocked process..."
            timeout 5 strace -p "$philo_pid" 2>/dev/null | head -20 || true
        fi
        
        # Force kill after giving time to observe
        sleep 2
        kill -9 "$philo_pid" 2>/dev/null || true
        return 0
    else
        echo -e "${GREEN}✓ No deadlock detected${NC}"
        return 1
    fi
}

# Function to demonstrate multiple rapid SIGINTs
stress_test() {
    echo -e "\n${BLUE}=== Stress Test: Multiple SIGINTs ===${NC}"
    
    local test_params="5 600 200 200 3"
    
    $PHILO_PROGRAM $test_params > "stress_test_output.log" 2>&1 &
    local philo_pid=$!
    
    echo "Starting stress test with PID: $philo_pid"
    
    # Send multiple SIGINTs rapidly
    for i in {1..5}; do
        sleep 1
        echo "Sending SIGINT #$i to PID $philo_pid"
        kill -INT "$philo_pid" 2>/dev/null || break
        
        if ! kill -0 "$philo_pid" 2>/dev/null; then
            echo "Process terminated after SIGINT #$i"
            return 1
        fi
    done
    
    # Check final state
    sleep 2
    if kill -0 "$philo_pid" 2>/dev/null; then
        echo -e "${RED}✗ Process stuck after multiple SIGINTs - DEADLOCK!${NC}"
        kill -9 "$philo_pid" 2>/dev/null || true
        return 0
    else
        echo -e "${GREEN}✓ Process terminated cleanly${NC}"
        return 1
    fi
}

# Main execution
main() {
    local deadlock_count=0
    local total_tests=0
    
    echo "Starting deadlock demonstration..."
    echo "Timestamp: $(date)"
    echo ""
    
    # Run standard test cases
    local i=1
    for test_case in "${TEST_CASES[@]}"; do
        if run_test "$test_case" "$i"; then
            ((deadlock_count++))
        fi
        ((total_tests++))
        ((i++))
        
        # Cleanup any hanging processes
        pkill -f "$PHILO_PROGRAM" 2>/dev/null || true
        sleep 1
    done
    
    # Run stress test
    if stress_test; then
        ((deadlock_count++))
    fi
    ((total_tests++))
    
    # Summary
    echo -e "\n${BLUE}=== DEADLOCK DEMONSTRATION SUMMARY ===${NC}"
    echo "Total tests run: $total_tests"
    echo -e "Deadlocks detected: ${RED}$deadlock_count${NC}"
    echo -e "Clean terminations: ${GREEN}$((total_tests - deadlock_count))${NC}"
    
    if [ $deadlock_count -gt 0 ]; then
        echo -e "\n${RED}🔒 DEADLOCK SUCCESSFULLY DEMONSTRATED!${NC}"
        echo "The program gets stuck when SIGINT interrupts mutex operations"
        echo ""
        echo "Check these files for details:"
        ls -la test_*_output.log stress_test_output.log 2>/dev/null || true
        echo ""
        echo "To fix this issue, the program should:"
        echo "1. Implement proper signal-safe mutex handling"
        echo "2. Use sigaction() with SA_RESTART instead of signal()"
        echo "3. Add cleanup handlers for graceful shutdown"
        echo "4. Check atomic 'stop' flag before mutex operations"
    else
        echo -e "\n${GREEN}No deadlocks detected in this run${NC}"
        echo "Try running the script multiple times or with different parameters"
    fi
    
    echo -e "\n${BLUE}Log file: $LOG_FILE${NC}"
}

# Cleanup function
cleanup() {
    echo "Cleaning up..."
    pkill -f "$PHILO_PROGRAM" 2>/dev/null || true
    exit 0
}

# Set trap for cleanup
trap cleanup SIGINT SIGTERM

# Run main function and log everything
{
    main
} 2>&1 | tee "$LOG_FILE"