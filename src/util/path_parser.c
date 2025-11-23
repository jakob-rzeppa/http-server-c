#include "path_parser.h"

int extract_notes_id(char *path)
{
    regex_t regex;
    regmatch_t matches[2];

    // Pattern: /notes/:id where :id is captured
    char *pattern = "^/notes/([0-9]+)$";

    // Compile regex
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
    {
        log_error("regex compilation failed");
        return FAILED;
    }

    // Execute regex
    if (regexec(&regex, path, 2, matches, 0) != 0)
    {
        log_error("invalid path format: expected /notes/:id");
        regfree(&regex);
        return FAILED;
    }

    // Extract id
    int id_len = matches[1].rm_eo - matches[1].rm_so;
    char *id_str = (char *)malloc(id_len + 1);
    strncpy(id_str, path + matches[1].rm_so, id_len);
    *(id_str + id_len) = '\0';

    // Convert to integer
    int id = atoi(id_str);

    free(id_str);
    regfree(&regex);

    if (id == -1)
    {
        // make sure the right error code is returned
        return FAILED;
    }

    return id;
}