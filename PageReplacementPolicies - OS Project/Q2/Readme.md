## **Multi Threaded Web Server**

## Introduction

The **Multi-Threaded Web Server** is a simple HTTP server built in C that uses threading to handle multiple client requests concurrently. Each client connection is processed in a separate thread, demonstrating efficient handling of simultaneous connections. The server responds with an HTML page that includes runtime and resource usage statistics, showcasing a practical implementation of multithreading and system resource tracking.

## Code Explanation

The key components of the code are:

1. **Socket Creation and Binding**:
    - socket() creates a TCP socket.
    - bind() binds the socket to a specific port and address.
2. **Listening and Accepting Connections**:
    - listen() sets the server to listen for incoming client connections.
    - accept() establishes a connection with a client.
3. **Threading for Concurrent Requests**:
    - Each client connection spawns a new thread using pthread_create().
    - Threads are detached with pthread_detach() to handle cleanup automatically.
4. **Client Request Handling**:
    - handle_client() processes each client's request. It calculates server runtime, gathers resource usage statistics, and formats a dynamic HTML response.
5. **Resource Tracking and Runtime Calculation**:
    - clock() tracks the server's runtime.
    - getrusage() collects CPU time and memory usage for generating response statistics.
6. **HTTP Response**:
    - The server sends a pre-defined HTML response dynamically populated with runtime and resource usage data.

## How to Compile and Run the Code

**Step 1: Install GCC**

1. Install the GCC compiler:

sudo apt update

sudo apt install build-essential

2. Verify installation:

gcc --version

** Step 2: Navigate to the File Location**

Navigate to the directory containing the code:

cd /path/to/your/code

**Step 3: Compile the Code**

Compile the server with pthread support:

gcc Q2_Multi_Threaded_Web_Server.c -o Q2_Multi_Threaded_Web_Server -pthread

**Step 4: Run the Server**

Start the server:

./Q2_Multi_Threaded_Web_Server

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
    - "Hello! This is Created by Multi-Threaded Web Server"
2. Dynamic statistics, including:
    - Server runtime.
    - User and system CPU time.
    - Maximum memory usage.

Additionally, the terminal logs:

- Client requests.
- Confirmation of responses sent to clients.