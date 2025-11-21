#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "/workspaces/http-server-c/src/response_handler.c"
#include "/workspaces/http-server-c/src/socket_handler.c"

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
    int port = bind_socket_to_port(server_socket);
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

    listen_for_connections(server_socket);

    printf("Shutdown server");
    close(server_socket);
    return EXIT_SUCCESS;
}
