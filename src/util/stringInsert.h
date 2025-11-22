#ifndef STRING_INSERT_H
#define STRING_INSERT_H

#include <string.h>

/**
 * Inserts a string into another, starting at a given index. 
 * The index will be updated to be at the character after the last insertion.
 *
 * @param target The string to be inserted to
 * @param targetBufferSize The max size of the string (including \0)
 * @param index The index to start inserting to
 * @param source The string to be inserted
 * @return 0 on success, -1 on failure
 */
int string_insert(char *target, int targetBufferSize, int *index, const char *source);

#endif // STRING_INSERT_H
