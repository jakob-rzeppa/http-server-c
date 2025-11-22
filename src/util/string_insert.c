#include "string_insert.h"

/**
 * Inserts a string into another, starting at a given index. The index will be updated to be at the character after the last insertion.
 *
 * @param target the string to be inserted to
 * @param targetBufferSize the max size of the string (including \0)
 * @param index the index to start inserting to
 * @param source the string to be inserted
 */
int string_insert(char *target, int targetBufferSize, int *index, const char *source)
{
    int sourceLength = strlen(source);
    if (*index + sourceLength >= targetBufferSize - 1)
        return -1;

    for (int i = 0; i < sourceLength; i++)
    {
        target[*index + i] = source[i];
    }

    *index += sourceLength;
    target[*index] = '\0';
    return 0;
}