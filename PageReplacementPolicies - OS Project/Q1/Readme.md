## **Multi Process Web Server**


## Introduction

The **Multi Process Web Server** is a simple HTTP server built in C. It demonstrates how to create a multi-process server capable of handling multiple client requests concurrently. The server provides an HTML response containing runtime statistics such as server run time, CPU usage, and memory usage, showcasing the integration of system calls and process management in a real-world application.

## Code Explanation

The code consists of several key components and functions:

1. **Socket Creation and Binding**:
    - socket() creates a server socket.
    - bind() assigns an address to the socket.
2. **Listening and Accepting Connections**:
    - listen() makes the server ready to accept incoming connections.
    - accept() waits for and establishes a connection with a client.
3. **Handling Multiple Clients**:
    - fork() is used to spawn a new process for each incoming client request, allowing concurrent processing.
4. **Response Preparation**:
    - A pre-defined HTML template is dynamically populated with the server's runtime and resource usage statistics using gettimeofday() and getrusage().
5. **System Resource Tracking**:
    - gettimeofday() captures server start and end times for calculating runtime.
    - getrusage() provides details about CPU time and memory usage.
6. **HTTP Response**:
    - The dynamically generated HTML is sent back to the client as a response.

## How to Compile and Run the C Code

**Step 1: Install GCC**

1. Install the GCC compiler:

sudo apt update

sudo apt install build-essential

2. Verify installation:

gcc --version

**Step 2: Navigate to the File Location**

 Use the cd command to move to the directory containing the code:

cd /path/to/your/code

**Step 3: Compile the Code**

 Compile the server:

gcc Q1_Multi_Process_Web_Server.c -o Q1_Multi_Process_Web_Server

**Step 4: Run the Server**

 Start the server:

./Q1_Multi_Process_Web_Server

**Step 5: Test in Browser**

 Open a web browser and navigate to:

<http://localhost:8090>

## Running the Makefile

Use these steps to run:

- 1. Navigate to the file directory:

cd /path/to/your/code

- 2. Build the project:

make

- 3. To run the server:

make run

## Expected Output

When you navigate to <http://localhost:8090> in your browser, you should see:

1. A webpage displaying the message:
    - "Hello! This is Created by Multi Process Web Server!"
2. Dynamic server statistics:
    - Server runtime.
    - User and system CPU time.
    - Maximum memory usage.

Additionally, in the terminal, the server logs:

- Client requests.
- Confirmation of response sent to the client.