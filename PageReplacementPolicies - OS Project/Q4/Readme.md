## **Task Distribution system**

## Introduction

The **Task Distribution System** is a multithreaded C program that simulates the processing of tasks through various "units." Each task undergoes multiple operations defined by unit IDs, such as addition, multiplication, and power functions. The program uses a global task queue, and multiple threads are responsible for processing tasks concurrently.

Tasks are read from a predefined queue and go through up to 5 processing units. The system demonstrates efficient multithreaded task management and processing, which is critical in parallel computing and real-time systems.

## What the Program Does

- **Task Processing**: Tasks are processed sequentially by multiple units:
  - **Unit 0**: Adds 7 to the task value.
  - **Unit 1**: Multiplies the task value by 2.
  - **Unit 2**: Raises the task value to the power of 5.
  - **Unit 3**: Subtracts 19 from the task value.
- **Multithreading**: Five threads process tasks concurrently, distributing the workload for efficiency.
- **Output**: After processing, each thread prints the task's final value along with the timestamp and thread ID.

## Code Explanation

1. **Task Structure**:
    - A Task structure stores the value to be processed.
    - The global task_queue holds the tasks to be processed.
2. **Task Processing**:
    - The process_task() function applies operations based on the unit ID.
3. **Multithreading**:
    - Each thread processes a task through all units using the task_worker() function.
4. **Time Measurement**:
    - get_current_time() captures the timestamp when tasks are processed.
5. **Main Function**:
    - Initializes the task queue.
    - Creates and joins threads to ensure task processing is completed.

## How to Compile and Run the Code

**Step 1: Install GCC**

1. Install the GCC compiler:

sudo apt update

sudo apt install build-essential

2. Verify installation:

gcc --version

**Step 2: Navigate to the File Location**

Move to the directory containing the code and tasks.txt:

cd /path/to/your/code

**Step 3: Compile the Code**

Compile with pthread and math libraries:

gcc -o Task_Distribution_System Q4_Task_Distribution_System.c -pthread -lm

**Step 4: Run the Program**

Execute the compiled program:

./Task_Distribution_System

## Running the Makefile

Use these steps:

- 1. Navigate to the directory:

cd /path/to/your/code

- 2. Build the project:

make

- 3. To run the server::

make run

## Expected Output

**The output includes:**

- Timestamp (in milliseconds).
- Thread ID (tid).
- Final value of each task.

**Example output:**

1736627180323 tid: 0 value: 537805

1736627180323 tid: 1 value: 1048557

1736627180323 tid: 2 value: 1889549

1736627180323 tid: 3 value: 3199981

1736627180323 tid: 4 value: 5153613