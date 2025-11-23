#ifndef PATH_PARSER_H
#define PATH_PARSER_H

#include "../common.h"

/**
 * Parse request path for notes id
 *
 * example path: "/notes/:id"
 *
 * @param fullPath the request path
 * @return id or FAILED
 */
int extract_notes_id(char *fullPath);

#endif // PATH_PARSER_H