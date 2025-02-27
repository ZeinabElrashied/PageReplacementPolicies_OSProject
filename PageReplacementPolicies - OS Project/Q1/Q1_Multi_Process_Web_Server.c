#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>  // Added for gettimeofday()
#include <time.h>

#define PORT 8090

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // HTML message with placeholders for runtime and resource usage
    char hello[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                    "<!DOCTYPE html><html><body>"
                    "<h2>Hello! This is Created by Multi Process Web Server!</h2>"
                    "<p>Server Run Time: %.2f seconds</p>"
                    "<p>User CPU time: %ld.%06ld seconds</p>"
                    "<p>System CPU time: %ld.%06ld seconds</p>"
                    "<p>Max memory usage: %ld kilobytes</p>"
                    "</body></html>";

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

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);  // Start the clock for runtime tracking

    while (1)
    {
        printf("\n+++++++ Waiting for a new connection ++++++++\n\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
        {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        if (fork() == 0)
        {
            close(server_fd);
            char buffer[30000] = {0};

            // Read client request
            read(new_socket, buffer, sizeof(buffer));

            printf("Client Request:\n%s\n", buffer);

            // Calculate runtime using gettimeofday
            gettimeofday(&end_time, NULL);
            double runtime = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

            // Output server runtime and resource usage
            struct rusage usage;
            getrusage(RUSAGE_SELF, &usage);

            // Format the HTML response with the actual values
            char response[1024];
            snprintf(response, sizeof(response),
                     hello,
                     runtime,
                     usage.ru_utime.tv_sec, usage.ru_utime.tv_usec,
                     usage.ru_stime.tv_sec, usage.ru_stime.tv_usec,
                     usage.ru_maxrss);

            // Send the HTTP response
            write(new_socket, response, strlen(response));
            printf("Response sent to client\n");

            close(new_socket);
            exit(0);
        }
        close(new_socket);
    }

    return 0;
}
