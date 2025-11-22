#include "/workspaces/http-server-c/src/common.h"

#include "/workspaces/http-server-c/src/socket_handler.c"
#include "/workspaces/http-server-c/src/connection_listener.c"

int main(int argc, char const *argv[])
{
    int server_socket;

    // creating the socket - 0 for default protocol (for SOCK_STREAM TCP)
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        log_error("socket failed: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Socket connected\n");

    // binding the socket to the PORT
    int port = bind_socket_to_port(server_socket);
    if (port < 0)
    {
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
        log_error("listen failed: %s", strerror(errno));
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    listen_for_connections(server_socket);

    printf("Shutdown server");
    close(server_socket);
    return EXIT_SUCCESS;
}
