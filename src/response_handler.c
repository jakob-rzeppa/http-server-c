#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

char *generateStatusCodeLine(int statusCode)
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

void sendSocketHeaders(int client_socket, int statusCode, int bodySize)
{
    // --- status code line ---
    char *statusCodeLine = generateStatusCodeLine(statusCode);
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
    printf(contentLengthLine);
    send(client_socket, contentLengthLine, strlen(contentLengthLine), 0);
    free(contentLengthLine);

    // --- newline ---
    char *newlineLine = "\r\n";
    send(client_socket, newlineLine, strlen(newlineLine), 0);
}

int sendResponse(int client_socket, int statusCode, char *body)
{
    sendSocketHeaders(client_socket, statusCode, strlen(body));

    send(client_socket, body, strlen(body), 0);
}