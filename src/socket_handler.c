#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <regex.h>
#include <errno.h>

#include "/workspaces/http-server-c/src/request_handler.c"

// The programm will try to connect to the PORT
// If the port is in use, it will try the next port, until reaching the MAX_PORT
#define PORT 3000
#define MAX_PORT 3005
#define MAX_QUEUED_CONNECTIONS 3

/**
 * Binds the socket to a port
 *
 * @return the port bound to or -1 for failed to bind port
 */
int bind_socket_to_port(int server_socket)
{
    struct sockaddr_in server_addr;

    int bind_res = -1; // initialized to an error res
    int port = PORT;

    server_addr.sin_family = PF_INET;         // uses the internet namespace
    server_addr.sin_addr.s_addr = INADDR_ANY; // the address to accept incoming messages
    server_addr.sin_port = htons(PORT);       // htons converts a 16-bit int from host byte order to network byte order
    do
    {
        server_addr.sin_port = htons(port);

        bind_res = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

        if (bind_res < 0)
        {
            port++;
        }
    } while ((bind_res < 0 && port <= MAX_PORT));

    if (bind_res < 0)
        return -1;
    else
        return port;
}

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
            printf("accept failed: %s\n", strerror(errno));
            continue;
        }

        printf("connection recieved\n");
        handle_request(client_socket);

        close(client_socket);
        client_socket = -1;
    }
}