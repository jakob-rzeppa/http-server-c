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
int get_notes(int id);

/**
 * Creates a new note
 */
int create_note(char *content);

/**
 * Updates an existing note
 */
int update_note(int id, char *content);

/**
 * Deletes a note
 */
int delete_note(int id);

#endif // NOTES_REPOSITORY_H
