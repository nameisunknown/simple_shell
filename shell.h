#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "shell.h"
#include <stdlib.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <errno.h>

/**
* struct specifier_format - Is a struct that contains format specifiers
* and format functions
* @specifier: Is the specifier character
* @func: Is the pointer to a format function
*/
typedef struct specifier_format
{
    char *specifier;
    int (*func)(va_list ptr, char *buffer, int *buffer_index);
} spec_format;

char **brkStr(char *strEntered, char *separator);
void handleError(void);
char *_findpath(char *cmd);
void free_entities(char *buffer, char **tokenizedstr);
int create_fork(char *full_path, char **tokenizedArgs, char *readString);
void free_tokenizedArgs(char *toksArgs[]);
void errnoValidation(void);
int _perror(const char *format, ...);
int print_int_format(va_list ptr, char *buffer, int *buffer_index);
int print_char_format(va_list ptr, char *buffer, int *buffer_index);
int print_string_format(va_list ptr, char *buffer, int *buffer_index);
int add_to_buffer(char *buffer, int *buffer_index, char src);
int free_buffer(char *buf, int *buf_index);

#endif
