#include "/workspaces/http-server-c/src/common.h"

#include "/workspaces/http-server-c/src/socket_handler.c"
#include "/workspaces/http-server-c/src/connection_listener.c"

int main(int argc, char const *argv[])
{
    int server_socket;

    // creating the socket
    if ((server_socket = create_socket()) == FAILED_SHOULD_EXIT)
    {
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // binding the socket
    if (bind_socket_to_port(server_socket) == FAILED_SHOULD_EXIT)
    {
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // listening to the socket
    if (listen_for_connections(server_socket) == FAILED_SHOULD_EXIT) {
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    log_info("Shutdown server");
    close(server_socket);
    return EXIT_SUCCESS;
}
