#ifndef NOTES_REPOSITORY_H
#define NOTES_REPOSITORY_H

#include "../common.h"

struct note
{
    int id;
    char *content;
};

/**
 * Retrieves all notes
 */
int get_notes(int client_socket);

/**
 * Creates a new note
 */
int create_note(int client_socket);

/**
 * Updates an existing note
 */
int update_note(int client_socket);

/**
 * Deletes a note
 */
int delete_note(int client_socket);

#endif // NOTES_REPOSITORY_H
