# Compiler and flags
CC = gcc
CFLAGS = -Wall -pthread

# Output file name
OUTPUT = Q1_Multi_Process_Web_Server

# Source files
SRC = Q1_Multi_Process_Web_Server.c

# Object files
OBJ = $(SRC:.c=.o)

# Default target: compile and link
all: $(OUTPUT)

# Linking the object files to create the executable
$(OUTPUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUTPUT)

# Compiling the C source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled object files and executable
clean:
	rm -f $(OBJ) $(OUTPUT)

# Run the compiled program
run: $(OUTPUT)
	./$(OUTPUT)

