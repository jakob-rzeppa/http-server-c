#include "response_handler.h"

char *generate_status_code_line(int statusCode)
{
    switch (statusCode)
    {
    case 200:
        return "HTTP/1.1 200 OK\r\n";
    case 400:
        return "HTTP/1.1 400 Bad Request\r\n";
    case 500:
        return "HTTP/1.1 500 Internal Server Error\r\n";
    default:
        return NULL;
    }
}

void send_socket_headers(int client_socket, int statusCode, int bodySize)
{
    // --- status code line ---
    char *statusCodeLine = generate_status_code_line(statusCode);
    send(client_socket, statusCodeLine, strlen(statusCodeLine), 0);

    // --- content type ---
    char *contentTypeLine = "Content-Type: application/json\r\n";
    send(client_socket, contentTypeLine, strlen(contentTypeLine), 0);

    // --- content length ---
    int contentLengthLineSize = 16 + 10 + 2;
    // 16 for "Content-length: "
    // 10 as a buffer for the number (max 32-Bit int 2,147,483,647)
    // 2 for "\r\n"
    char *contentLengthLine = (char *)malloc(sizeof(char) * (contentLengthLineSize + 1 /* esc char */));
    snprintf(contentLengthLine, contentLengthLineSize, "Content-Length: %d\r\n", bodySize);
    send(client_socket, contentLengthLine, strlen(contentLengthLine), 0);
    free(contentLengthLine);

    // --- newline ---
    char *newlineLine = "\r\n";
    send(client_socket, newlineLine, strlen(newlineLine), 0);
}

int send_response(int client_socket, int statusCode, char *bodyFormat, ...)
{
    char *body = (char *)malloc(sizeof(char) * RESPONSE_BUFFER_SIZE);

    va_list args;
    va_start(args, bodyFormat);
    int snprintf_res = vsnprintf(body, RESPONSE_BUFFER_SIZE, bodyFormat, args);
    va_end(args);

    if (snprintf_res < 0 || snprintf_res >= RESPONSE_BUFFER_SIZE) {
        log_error("response body overflow: exceeded buffer size of %d with %d characters", RESPONSE_BUFFER_SIZE, snprintf_res);
        free(body);
        body = NULL;

        char *error_body = "{\"message\": \"response body overflow\"}";
        send_socket_headers(client_socket, 500, strlen(error_body));
        send(client_socket, error_body, strlen(error_body), 0);

        return FAILED_AND_SEND_RESPONSE;
    }

    send_socket_headers(client_socket, statusCode, strlen(body));
    send(client_socket, body, strlen(body), 0);

    free(body);
    return SUCCESSFUL;
}