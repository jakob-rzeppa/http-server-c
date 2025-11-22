#ifndef NOTES_CONTROLLER_H
#define NOTES_CONTROLLER_H

#include "../common.h"
#include "../repository/notes_repository.h"
#include "../response/response_handler.h"

/**
 * Handles GET request for notes
 */
int handle_get_notes_request(int client_socket);

/**
 * Handles POST request to create a note
 */
int handle_create_note_request(int client_socket, char *body);

/**
 * Handles PUT request to update a note
 */
int handle_update_note_request(int client_socket, char *body);

/**
 * Handles DELETE request to delete a note
 */
int handle_delete_note_request(int client_socket);

#endif // NOTES_CONTROLLER_H
