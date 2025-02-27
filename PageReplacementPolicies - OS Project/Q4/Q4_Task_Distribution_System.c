#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MAX_TASKS 5
#define NUM_UNITS 4
#define NUM_THREADS 5

// Task structure
typedef struct task {
    long long value; // Use long long to avoid overflow
} Task;

// Global task queue
Task task_queue[MAX_TASKS];

// Function to get the current time in milliseconds
long get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

// Task processing function
void process_task(Task *task, int unit_id) {
    switch (unit_id) {
        case 0: // Unit 0: Add 7
            task->value += 7;
            break;
        case 1: // Unit 1: Multiply by 2
            task->value *= 2;
            break;
        case 2: // Unit 2: Raise to power 5
            task->value = (long long)pow(task->value, 5);
            break;
        case 3: // Unit 3: Subtract 19
            task->value -= 19;
            break;
    }
}

// Worker function to process the tasks
void* task_worker(void* arg) {
    int tid = *((int*)arg); // Thread ID
    int task_id = tid % MAX_TASKS; // Each thread works on a different task based on its ID

    // Process the task through all the units
    for (int j = 0; j < NUM_UNITS; j++) {
        process_task(&task_queue[task_id], j);
    }

    // Print the final task value with timestamp
    printf("%ld tid: %d value: %lld\n", get_current_time(), tid, task_queue[task_id].value);

    return NULL;
}

int main() {
    // Initialize tasks with some values
    for (int i = 0; i < MAX_TASKS; i++) {
        task_queue[i].value = i;  // Initial value for each task
    }

    // Thread IDs
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, task_worker, (void*)&thread_ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
