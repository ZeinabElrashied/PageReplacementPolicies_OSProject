# Compiler
CC = gcc

# Compiler flags
CFLAGS = -pthread -lm

# Target binary
TARGET = Task_Distribution_System

# Source files
SRC = Q4_Task_Distribution_System.c

# Object files
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -pthread -lm
SRC = Q4_Task_Distribution_System.c
OBJ = Q4_Task_Distribution_System.o
EXEC = Task_Distribution_System

# Default target: build the program
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(CFLAGS)

# Compile source code into object files
$(OBJ): $(SRC)
	$(CC) -c $(SRC) $(CFLAGS)

# Clean up generated files
clean:
	rm -f $(OBJ) $(EXEC)

# Run the program (assuming task.txt exists)
run: $(EXEC)
	./$(EXEC) tasks.txt


