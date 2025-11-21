#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <regex.h>
#include <errno.h>

#include "/workspaces/http-server-c/src/notes_controller.c"

// The programm will try to connect to the PORT
// If the port is in use, it will try the next port, until reaching the MAX_PORT
#define PORT 3000
#define MAX_PORT 3005
#define MAX_QUEUED_CONNECTIONS 3
#define REQUEST_BUFFER_SIZE 1024

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

int handle_client(int client_socket)
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
            // regex compilation failed
            free(buffer);
            return -1;
        }

        // Execute regex
        if (regexec(&regex, buffer, 3, matches, 0) != 0)
        {
            // invalid http header
            regfree(&regex);
            free(buffer);
            return -1;
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

        if (strcmp(url_encoded_path, "/notes") == 0)
        {
            if (strcmp(method, "GET") == 0)
            {
                handle_get_notes_request(client_socket);
            }
            else if (strcmp(method, "POST") == 0)
            {
                handle_create_note_request(client_socket);
            }
            else if (strcmp(method, "PUT") == 0)
            {
                handle_update_note_request(client_socket);
            }
            else if (strcmp(method, "DELETE") == 0)
            {
                handle_delete_note_request(client_socket);
            }
            else
            {
                // no valid http method for path
                free(method);
                free(url_encoded_path);
                regfree(&regex);
                free(buffer);
                return -1;
            }
        }
        else
        {
            // no valid path
            free(method);
            free(url_encoded_path);
            regfree(&regex);
            free(buffer);
            return -1;
        }

        free(method);
        free(url_encoded_path);
        regfree(&regex);
    }

    free(buffer);
    return 0;
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
        handle_client(client_socket);

        close(client_socket);
        client_socket = -1;
    }
}