
#include "notes_repository.h"

/**
 * File structure:
 * id;content-size;content
 * example: 5;12;example note
 */

struct note
{
    int id;
    char *content;
};

int get_notes(int id)
{
    return SUCCESSFUL;
}

int create_note(char *content)
{
    FILE *fptr;

    // --- FIND THE ID ---
    fptr = fopen(DATABASE_PATH, "r" /* read mode */);
    if (fptr == NULL)
    {
        log_error("create_note failed: could not open file: %s", strerror(errno));
        return FAILED;
    }

    int highest_id = 0;
    bool is_end_of_file = false;
    do
    {
        char id_buffer[10] = ""; // 10 because a 32-Bit int has max 10 digits

        int c;

        int index = 0;
        while ((c = getc(fptr)) != EOF && c != ';')
        {
            id_buffer[index++] = c;
        }

        int id = atoi(id_buffer);

        if (id > highest_id)
            highest_id = id;

        while ((c = fgetc(fptr)) != EOF && c != '\n')
        {
        }

        if (c == EOF)
            is_end_of_file = true;

    } while (!is_end_of_file);

    fclose(fptr);
    fptr = NULL;

    // --- ASSEMBLE THE LINE ---
    int content_size = strlen(content);
    int line_size = 3 /* seperators */ + 10 /* id size */ + 10 /* content_size size */ + content_size + 1 /* esc char */;
    char *line = (char *)malloc(sizeof(char) * (line_size));

    int snprintf_res = snprintf(line, line_size, "%d;%d;%s\n", highest_id + 1, content_size, content);
    if (snprintf_res < 0 || snprintf_res >= line_size)
    {
        log_error("create_note failed: content buffer overflow");
        free(line);
        return FAILED;
    }

    // --- APPEND THE LINE ---
    fptr = fopen(DATABASE_PATH, "a" /* append mode */);
    if (fptr == NULL)
    {
        log_error("create_note failed: could not open file: %s", strerror(errno));
        free(line);
        return FAILED;
    }

    fprintf(fptr, line);

    fclose(fptr);
    fptr = NULL;

    free(line);
    return SUCCESSFUL;
}

int update_note(int id, char *content)
{
    return SUCCESSFUL;
}

int delete_note(int id)
{
    return SUCCESSFUL;
}