#include "request_handler.h"

#define REQUEST_BUFFER_SIZE 1024

int handle_request(int client_socket)
{
    char *buffer = (char *)malloc(sizeof(char) * REQUEST_BUFFER_SIZE);

    ssize_t bytes_received = recv(client_socket, buffer, REQUEST_BUFFER_SIZE, 0);
    if (bytes_received > 0)
    {
        regex_t regex;
        // matches[0] = entire match
        // matches[1] = first capture group (GET|POST|PUT|DELETE)
        // matches[2] = second capture group (path)
        regmatch_t matches[3];

        // Pattern: (GET|POST|PUT|DELETE) <space> (path) <space> HTTP/version
        const char *pattern = "^(GET|POST|PUT|DELETE) ([^ ]+) HTTP/[0-9]\\.[0-9]";

        // Compile regex
        if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
        {
            log_error("regex compilation failed");
            free(buffer);
            return FAILED_SHOULD_EXIT;
        }

        // Execute regex
        if (regexec(&regex, buffer, 3, matches, 0) != 0)
        {
            log_error("invalid request: invalid header");
            regfree(&regex);
            free(buffer);
            char *res_body = "{ \"message\": \"invalid request: invalid header\"}";
            send(client_socket, res_body, strlen(res_body), 0);
            return FAILED_AND_SEND_RESPONSE;
        }

        // extract method
        int method_len = matches[1].rm_eo - matches[1].rm_so;
        char *method = (char *)malloc(method_len + 1 /* esc char */);
        strncpy(method, buffer + matches[1].rm_so, method_len);
        *(method + method_len) = '\0';

        // extract url_encoded_path
        int url_encoded_path_len = matches[2].rm_eo - matches[2].rm_so;
        char *url_encoded_path = (char *)malloc(url_encoded_path_len + 1 /* esc char */);
        strncpy(url_encoded_path, buffer + matches[2].rm_so, url_encoded_path_len);
        *(url_encoded_path + url_encoded_path_len) = '\0';

        // error handling not nessesary since all errors from this point onward should not exit the program
        route_request(client_socket, method, url_encoded_path);

        free(method);
        free(url_encoded_path);
        regfree(&regex);
    }

    free(buffer);
    return SUCCESSFUL;
}