#include "body_parser.h"

// Parse create request - MAKE SURE TO FREE THE RETURN VALUE
char *parse_create_request(char *request_body)
{
    regex_t regex;
    // matches[0] = entire match
    // matches[1] = the content
    regmatch_t matches[2];

    char *pattern = "\\{[[:space:]]*\"content\"[[:space:]]*:[[:space:]]*\"([^\"]*)\"[[:space:]]*\\}";

    // Compile regex
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
    {
        log_error("regex compilation failed");
        return NULL;
    }

    // Execute regex
    if (regexec(&regex, request_body, 2, matches, 0) != 0)
    {
        log_error("invalid request body");
        regfree(&regex);
        return NULL;
    }

    // extract the content
    int content_size = matches[1].rm_eo - matches[1].rm_so;
    char *content = (char *)malloc(content_size + 1 /* esc char */);
    strncpy(content, request_body + matches[1].rm_so, content_size);
    *(content + content_size) = '\0';

    regfree(&regex);
    return content; // MAKE SURE TO FREE THE CONTENT
}

// Parse update request - MAKE SURE TO FREE THE RETURN VALUE
char *parse_update_request(char *request_body)
{
    regex_t regex;
    // matches[0] = entire match
    // matches[1] = the content
    regmatch_t matches[2];

    char *pattern = "\\{[[:space:]]*\"content\"[[:space:]]*:[[:space:]]*\"([^\"]*)\"[[:space:]]*\\}";

    // Compile regex
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
    {
        log_error("regex compilation failed");
        return NULL;
    }

    // Execute regex
    if (regexec(&regex, request_body, 2, matches, 0) != 0)
    {
        log_error("invalid request body");
        regfree(&regex);
        return NULL;
    }

    // extract the content
    int content_size = matches[1].rm_eo - matches[1].rm_so;
    char *content = (char *)malloc(content_size + 1 /* esc char */);
    strncpy(content, request_body + matches[1].rm_so, content_size);
    *(content + content_size) = '\0';

    regfree(&regex);
    return content; // MAKE SURE TO FREE THE CONTENT
}