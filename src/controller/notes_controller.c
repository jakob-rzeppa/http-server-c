#include "notes_controller.h"

#include "../util/json_parser.h"

int handle_get_notes_request(int client_socket, char *path)
{

    send_response(client_socket, 200, "{\"message\": \"success\"}");
}

int handle_create_note_request(int client_socket, char *path, char *body)
{
    char *content = parse_create_request(body); // MAKE SURE TO FREE THE CONTENT
    if (content == NULL)
    {
        send_response(client_socket, 400, "{\"message\": \"invalid request body\"}");
        return FAILED_AND_SEND_RESPONSE;
    }

    send_response(client_socket, 200, content);

    free(content);
    return SUCCESSFUL;
}

int handle_update_note_request(int client_socket, char *path, char *body)
{
    char *content = parse_update_request(body); // MAKE SURE TO FREE THE CONTENT
    if (content == NULL)
    {
        send_response(client_socket, 400, "{\"message\": \"invalid request body\"}");
        return FAILED_AND_SEND_RESPONSE;
    }

    send_response(client_socket, 200, content);

    free(content);
    return SUCCESSFUL;
}

int handle_delete_note_request(int client_socket, char *path)
{

    send_response(client_socket, 200, "{\"message\": \"success\"}");
}