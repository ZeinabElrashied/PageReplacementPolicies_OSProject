# Compiler and flags
CC = gcc
CFLAGS = -Wall -pthread
SRC = Q2_Multi_Threaded_Web_Server.c
OBJ = Q2_Multi_Threaded_Web_Server.o
OUT = Q2_Multi_Threaded_Web_Server

# Default target to build the executable
all: $(OUT)

# Build the executable from object files
$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT)

# Compile the source code to object file
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

# Clean up compiled files
clean:
	rm -f $(OBJ) $(OUT)

# Run the server
run: $(OUT)
	./$(OUT)
