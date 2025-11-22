#include "/workspaces/http-server-c/src/common.h"

/**
 * Creates a TCP socket.
 * 
 * @return (if successful) server_socket or FAILED_SHOULD_EXIT
 */
int create_socket() {
    int server_socket;

    // 0 for default protocol (for SOCK_STREAM TCP)
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        log_error("socket failed: %s", strerror(errno));
        return FAILED_SHOULD_EXIT;
    }

    log_info("Socket connected\n");
    return server_socket;
}

/**
 * Binds the socket to a port and loggs success message
 *
 * @return SUCCESSFUL or FAILED_SHOULD_EXIT
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
            log_error("port %d already in use", port);
            port++;
        }
    } while ((bind_res < 0 && port <= MAX_PORT));

    if (bind_res < 0)
    {
        log_error("no avaliable port found");
        return FAILED_SHOULD_EXIT;
    }

    log_info("Socket bound to PORT %d\n", port);
    return SUCCESSFUL;
}