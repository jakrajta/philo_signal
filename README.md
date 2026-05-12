# 🍝 42_Philosophers

A C implementation of the classic Dining Philosophers problem using threads and mutexes.

## Description

This program simulates the Dining Philosophers problem, where multiple philosophers sit around a table and alternate between thinking, eating, and sleeping. Each philosopher needs two forks to eat, but there are only as many forks as philosophers, leading to potential deadlock situations.

The program uses POSIX threads (pthreads) and mutexes to synchronize access to shared resources (forks). It includes proper handling of edge cases like a single philosopher scenario and implements a monitoring thread to detect philosopher deaths.

## Features

- Thread-safe implementation using mutexes
- Handles SIGINT signal for graceful shutdown
- Supports variable number of philosophers and timing parameters
- Special handling for single philosopher case
- Colored output for better visualization
- Atomic operations for thread-safe signal handling

## Usage

### Compilation

```bash
make
```

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

### Arguments

- `number_of_philosophers`: Number of philosophers and forks (1-200)
- `time_to_die`: Time in milliseconds after which a philosopher dies if they haven't eaten
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
- `number_of_meals` (optional): Number of meals each philosopher must eat before the simulation stops

### Examples

```bash
# 5 philosophers, die after 800ms, eat for 200ms, sleep for 200ms
./philo 5 800 200 200

# 4 philosophers, die after 410ms, eat for 200ms, sleep for 200ms, each eats 10 times
./philo 4 410 200 200 10
```

## Program Behavior

- Philosophers alternate between eating, sleeping, and thinking
- Each philosopher needs to acquire two forks (left and right) to eat
- If a philosopher doesn't eat within the `time_to_die` limit, they die and the simulation stops
- The program handles the deadlock prevention by ensuring philosophers pick up forks in a specific order
- Colored output shows different activities:
  - **Blue**: Thinking
  - **Magenta**: Sleeping
  - **Cyan**: Eating
  - **Red**: Death

## Requirements

- POSIX-compliant system with pthreads support
- C compiler (cc/gcc)
- Make build system


## Building

```bash
make
```

### Clean and Rebuild

```bash
make clean
make fclean
make re
```