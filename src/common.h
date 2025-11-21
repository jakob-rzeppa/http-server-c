#ifndef COMMON_H
#define COMMON_H

// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Network includes
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

// Utilities
#include <errno.h>
#include <regex.h>

// Project-wide constants
#define PORT 3000     // The programm will try to connect to the PORT
#define MAX_PORT 3010 // If the port is in use, it will try the next port, until reaching the MAX_PORT
#define MAX_QUEUED_CONNECTIONS 3
#define BUFFER_SIZE 4096

// Shared function declarations
int string_insert(char *target, int targetBufferSize, int *index, const char *source);
void log_error(const char *format, ...);

#endif // COMMON_H