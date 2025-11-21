#include <string.h>

#include "/workspaces/http-server-c/src/notes_controller.c"

int route_request(int client_socket, char *method, char *path)
{
    if (strcmp(path, "/notes") == 0)
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
            return -1;
        }
    }
    else
    {
        // no valid path
        return -1;
    }
}