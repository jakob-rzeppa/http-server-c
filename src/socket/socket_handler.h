#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

#include "../common.h"

/**
 * Creates a TCP socket.
 * 
 * @return (if successful) server_socket or FAILED_SHOULD_EXIT
 */
int create_socket();

/**
 * Binds the socket to a port and logs success message
 *
 * @return SUCCESSFUL or FAILED_SHOULD_EXIT
 */
int bind_socket_to_port(int server_socket);

#endif // SOCKET_HANDLER_H
