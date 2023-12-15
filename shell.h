#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "shell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

char **brkStr(char *strEntered, char *separator);
void handleError(void);
char *_findpath(char *cmd);
void free_entities(char *buffer, char **tokenizedstr);
void errnoValidation(void);

#endif
