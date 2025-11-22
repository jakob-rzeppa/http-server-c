#ifndef LOGGER_H
#define LOGGER_H

#include "common.h"

/**
 * Logs an info message
 *
 * @param format Printf-style format string
 * @param ... Variable arguments
 */
void log_info(const char *format, ...);

/**
 * Logs an error message
 *
 * @param format Printf-style format string
 * @param ... Variable arguments
 */
void log_error(const char *format, ...);

#endif // LOGGER_H
