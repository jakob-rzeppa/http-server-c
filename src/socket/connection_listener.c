#include "connection_listener.h"

int listen_for_connections(int server_socket)
{
    if ((listen(server_socket, MAX_QUEUED_CONNECTIONS)) < 0)
    {
        log_error("listen failed: %s", strerror(errno));
        return FAILED_SHOULD_EXIT;
    }

    printf("Listening to connections...\n");

    int handle_request_err;
    do {
        // reset err var
        handle_request_err = SUCCESSFUL;

        // client info
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket;

        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0)
        {
            log_error("accept failed: %s", strerror(errno));
            continue;
        }

        printf("connection recieved\n");
        handle_request_err = handle_request(client_socket);

        close(client_socket);
        client_socket = -1; // reset client_socket var
    } while (handle_request_err != FAILED_SHOULD_EXIT);

    return FAILED_SHOULD_EXIT;
}