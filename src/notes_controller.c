#include "notes_controller.h"

int handle_get_notes_request(int client_socket)
{

    send_response(client_socket, 200, "{\"message\": \"success\"}");
}

int handle_create_note_request(int client_socket)
{

    send_response(client_socket, 200, "{\"message\": \"success\"}");
}

int handle_update_note_request(int client_socket)
{

    send_response(client_socket, 200, "{\"message\": \"success\"}");
}

int handle_delete_note_request(int client_socket)
{

    send_response(client_socket, 200, "{\"message\": \"success\"}");
}