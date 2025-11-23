#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "../common.h"

/**
 * Parse create request - MAKE SURE TO FREE THE RETURN VALUE
 *
 * {
 *     "content": "example content"
 * }
 * @param request_body the json string
 * @return the content string (MAKE SURE TO FREE THE MEMORY) or NULL if failed
 */
char *parse_create_request(char *request_body);

/**
 * Parse update request - MAKE SURE TO FREE THE RETURN VALUE
 *
 * {
 *     "content": "example content"
 * }
 * @param request_body the json string
 * @return the content string (MAKE SURE TO FREE THE MEMORY) or NULL if failed
 */
char *parse_update_request(char *request_body);

#endif // JSON_PARSER_H