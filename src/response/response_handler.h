#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H

#include "../common.h"
#include "../util/string_insert.h"

/**
 * Generates the HTTP status line for a given status code
 *
 * @param statusCode The HTTP status code
 * @return The status line string
 */
char *generate_status_code_line(int statusCode);

/**
 * Sends socket headers to the client
 *
 * @param client_socket The socket descriptor
 * @param statusCode The HTTP status code
 * @param bodySize The size of the response body
 */
void send_socket_headers(int client_socket, int statusCode, int bodySize);

/**
 * Sends a complete HTTP response to the client
 *
 * @param client_socket The socket descriptor
 * @param status_code The HTTP status code
 * @param bodyFormat The response body - Printf-style format string
 * @param ... Variable arguments
 * @return SUCCESSFUL or error code
 */
int send_response(int client_socket, int status_code, char *bodyFormat, ...);

#endif // RESPONSE_HANDLER_H
