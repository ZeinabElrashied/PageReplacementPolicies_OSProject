#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/resource.h>

#define PORT 8090

// Function to handle each client
void *handle_client(void *arg)
{
    int new_socket = *(int *)arg;
    free(arg);

    // HTML response template
    char hello[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                   "<!DOCTYPE html><html><body>"
                   "<h2>Hello! This is Created by Multi-Threaded Web Server</h2>"
                   "<p>Server Run Time: %.2f seconds</p>"
                   "<p>User CPU time: %ld.%06ld seconds</p>"
                   "<p>System CPU time: %ld.%06ld seconds</p>"
                   "<p>Max memory usage: %ld kilobytes</p>"
                   "</body></html>";

    // Read the client request (not used for response generation in this case)
    char buffer[30000] = {0};
    read(new_socket, buffer, 30000);
    printf("Client Request:\n%s\n", buffer);

    // Calculate runtime
    static clock_t start_time = 0;
    if (start_time == 0) start_time = clock(); // Start time only once

    clock_t end_time = clock();
    double runtime = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Resource usage
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    // Prepare the response
    char response[1024];
    snprintf(response, sizeof(response),
             hello,
             runtime,
             usage.ru_utime.tv_sec, usage.ru_utime.tv_usec,
             usage.ru_stime.tv_sec, usage.ru_stime.tv_usec,
             usage.ru_maxrss);

    // Send the response
    write(new_socket, response, strlen(response));
    printf("Response sent to client\n");

    close(new_socket);
    return NULL;
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d\n", PORT);
    printf("Go to http://localhost:8090 to test it\n");

    while (1)
    {
        printf("\n+++++++ Waiting for a new connection ++++++++\n\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
        {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        pthread_t thread_id;
        int *pclient = malloc(sizeof(int));
        *pclient = new_socket;

        if (pthread_create(&thread_id, NULL, handle_client, pclient) != 0)
        {
            perror("Thread creation failed");
            free(pclient);
        }

        pthread_detach(thread_id);
    }

    return 0;
}
