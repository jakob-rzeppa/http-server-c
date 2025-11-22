#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "common.h"
#include "request_router.h"

/**
 * Handles an incoming HTTP request from a client
 *
 * @param client_socket The socket descriptor for the client connection
 * @return SUCCESSFUL, FAILED, FAILED_SHOULD_EXIT, or FAILED_AND_SEND_RESPONSE
 */
int handle_request(int client_socket);

#endif // REQUEST_HANDLER_H
