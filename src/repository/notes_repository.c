
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
    int content_size = strlen(content);
    int line_size = 3 /* seperators */ + 10 /* id size */ + 10 /* content_size size */ + content_size + 1 /* esc char */;
    char *line = (char *)malloc(sizeof(char) * (line_size));

    int snprintf_res = snprintf(line, line_size, "%d;%d;%s\n", 1, content_size, content);
    if (snprintf_res < 0 || snprintf_res >= line_size)
    {
        log_error("create_note failed: content buffer overflow");
        free(line);
        return FAILED;
    }

    // append to file

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