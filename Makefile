CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -pthread

# Source directories
SRC_DIR = src
OBJ_DIR = build

# Source files 
SRC = activities.c \
	  handle_threads.c \
	  init_structs.c \
	  input_control.c \
	  main.c \
	  monitor.c \
	  my_atoi.c \
	  one_philo.c \
	  print.c \
	  routine.c \
	  time.c 
	  
# Object files (automacally fill of prefic src/)
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

NAME = philo

# Default target
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Build final binary
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile  .c to .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Removing .o
clean:
	rm -rf $(OBJ_DIR)

# Full cleaning
fclean: clean
	rm -f $(NAME)

# Recompilation
re: fclean all

.PHONY: all clean fclean re

.SILENT:


# valgrind --tool=helgrind ./philo 5 800 200 200