#include "request_router.h"

int route_request(int client_socket, char *method, char *path, char* body)
{
    if (strcmp(path, "/notes") == 0)
    {
        if (strcmp(method, "GET") == 0)
        {
            handle_get_notes_request(client_socket);
        }
        else if (strcmp(method, "POST") == 0)
        {
            handle_create_note_request(client_socket, body);
        }
        else if (strcmp(method, "PUT") == 0)
        {
            handle_update_note_request(client_socket, body);
        }
        else if (strcmp(method, "DELETE") == 0)
        {
            handle_delete_note_request(client_socket);
        }
        else
        {
            log_error("invalid request: invalid method %s for %s", method, path);
            return FAILED;
        }
    }
    else
    {
        log_error("invalid request: invalid path %s", path);
        return FAILED;
    }

    return SUCCESSFUL;
}