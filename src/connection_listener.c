#include "/workspaces/http-server-c/src/common.h"

void listen_for_connections(int server_fd)
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
            log_error("accept failed: %s", strerror(errno));
            continue;
        }

        printf("connection recieved\n");
        handle_request(client_socket);

        close(client_socket);
        client_socket = -1;
    }
}