#include "request_router.h"

int route_request(int client_socket, char *method, char *path, char* body)
{
    // compare first 6 characters to /notes
    if (strncmp(path, "/notes", 6) == 0)
    {
        if (strcmp(method, "GET") == 0)
        {
            log_info("handling %s %s request", method, path);
            handle_get_notes_request(client_socket, path);
        }
        else if (strcmp(method, "POST") == 0)
        {
            log_info("handling %s %s request", method, path);
            handle_create_note_request(client_socket, path, body);
        }
        else if (strcmp(method, "PUT") == 0)
        {
            log_info("handling %s %s request", method, path);
            handle_update_note_request(client_socket, path, body);
        }
        else if (strcmp(method, "DELETE") == 0)
        {
            log_info("handling %s %s request", method, path);
            handle_delete_note_request(client_socket, path);
        }
        else
        {
            log_error("invalid request: invalid method %s for %s", method, path);
            send_response(client_socket, 400, "{\"message\": \"invalid request: invalid method %s for %s\"}", method, path);
            return FAILED_AND_SEND_RESPONSE;
        }
    }
    else
    {
        log_error("invalid request: invalid path %s", path);
            send_response(client_socket, 400, "{\"message\": \"invalid request: invalid path %s\"}", path);
        return FAILED_AND_SEND_RESPONSE;
    }

    return SUCCESSFUL;
}