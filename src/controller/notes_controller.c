#include "notes_controller.h"

#include "../util/body_parser.h"
#include "../util/path_parser.h"
#include "../repository/notes_repository.h"

int handle_get_notes_request(int client_socket, char *path)
{
    char *body_buffer = (char *)malloc(sizeof(char) * RESPONSE_BODY_SIZE);

    if (get_notes_as_json(body_buffer, RESPONSE_BODY_SIZE) == FAILED)
    {
        send_response(client_socket, 400, "{\"message\": \"response body buffer overflow\"}");
        return FAILED_AND_SEND_RESPONSE;
    }

    send_response(client_socket, 200, body_buffer);

    free(body_buffer);

    return SUCCESSFUL;
}

int handle_create_note_request(int client_socket, char *path, char *body)
{
    char *content = parse_create_request(body); // MAKE SURE TO FREE THE CONTENT
    if (content == NULL)
    {
        send_response(client_socket, 400, "{\"message\": \"invalid request body\"}");
        return FAILED_AND_SEND_RESPONSE;
    }

    if (create_note(content) == FAILED)
    {
        send_response(client_socket, 400, "{\"message\": \"creating of the note failed\"}");
        return FAILED_AND_SEND_RESPONSE;
    }

    send_response(client_socket, 200, "{\"message\": \"succesfully created note\"}");

    free(content);
    return SUCCESSFUL;
}

int handle_update_note_request(int client_socket, char *path, char *body)
{
    int id = extract_notes_id(path);
    if (id == FAILED)
    {
        send_response(client_socket, 400, "{\"message\": \"invalid path: couldn't extract id\"}");
        return FAILED_AND_SEND_RESPONSE;
    }

    char *content = parse_update_request(body); // MAKE SURE TO FREE THE CONTENT
    if (content == NULL)
    {
        send_response(client_socket, 400, "{\"message\": \"invalid request body\"}");
        return FAILED_AND_SEND_RESPONSE;
    }

    if (update_note(id, content) == FAILED)
    {
        send_response(client_socket, 400, "{\"message\": \"updating of the note failed - probably because the id does not exist\"}");
        return FAILED_AND_SEND_RESPONSE;
    }

    send_response(client_socket, 200, content);

    free(content);
    return SUCCESSFUL;
}

int handle_delete_note_request(int client_socket, char *path)
{
    int id = extract_notes_id(path);
    if (id == FAILED)
    {
        send_response(client_socket, 400, "{\"message\": \"invalid path: couldn't extract id\"}");
        return FAILED_AND_SEND_RESPONSE;
    }

    if (delete_note(id) == FAILED)
    {
        send_response(client_socket, 400, "{\"message\": \"deletion of the note failed\"}");
        return FAILED_AND_SEND_RESPONSE;
    }

    send_response(client_socket, 200, "{\"message\": \"%d\"}", id);

    return SUCCESSFUL;
}