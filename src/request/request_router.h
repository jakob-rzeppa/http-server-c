#ifndef REQUEST_ROUTER_H
#define REQUEST_ROUTER_H

#include "../common.h"
#include "../controller/notes_controller.h"

/**
 * Routes HTTP requests to appropriate handlers
 *
 * @param client_socket The socket descriptor for the client connection
 * @param method The HTTP method (GET, POST, PUT, DELETE)
 * @param path The request path
 * @return SUCCESSFUL or error code
 */
int route_request(int client_socket, char *method, char *path, char *body);

#endif // REQUEST_ROUTER_H
