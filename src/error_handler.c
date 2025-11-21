#include "/workspaces/http-server-c/src/common.h"

void log_error(const char *format, ...)
{
    va_list args;

    va_start(args, format);

    fprintf(stderr, "[ERROR] ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);
}