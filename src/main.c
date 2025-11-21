#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "/workspaces/http-server-c/src/response_handler.c"
#include "/workspaces/http-server-c/src/socket_handler.c"

#define MAX_QUEUED_CONNECTIONS 3

void listenForConnections(int server_fd)
{
    printf("Listening to connections...\n");

    while (1)
    {
        // client info
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket;

        client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0)
        {
            perror("accept failed");
            continue;
        }

        printf("connection recieved");

        char *body = "{\"t\": \"1\"}";
        sendResponse(client_socket, 200, body);

        close(client_socket);
        client_socket = -1;
    }
}

int main(int argc, char const *argv[])
{
    int server_socket;

    // creating the socket - 0 for default protocol (for SOCK_STREAM TCP)
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket connected\n");

    // binding the socket to the PORT
    int port = bindSocketToPort(server_socket);
    if (port < 0)
    {
        perror("bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket bound to PORT %d\n", port);
    }

    // listening to the socket
    if ((listen(server_socket, MAX_QUEUED_CONNECTIONS)) < 0)
    {
        perror("listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    listenForConnections(server_socket);

    printf("Shutdown server");
    close(server_socket);
    return EXIT_SUCCESS;
}
