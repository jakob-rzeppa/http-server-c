#ifndef CONNECTION_LISTENER_H
#define CONNECTION_LISTENER_H

#include "../common.h"
#include "../request/request_handler.h"

/**
 * Listens for incoming connections on the socket
 *
 * @return SUCCESSFUL or FAILED_SHOULD_EXIT
 */
int listen_for_connections(int server_socket);

#endif // CONNECTION_LISTENER_H
