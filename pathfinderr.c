#include "shell.h"

/**
 * _findpath - finds path of a command entered
 *
 * @cmd: the command entered
 * Return: NULL on error, and buffer on success
 */
char *_findpath(char *cmd)
{
	char *dir_topath = NULL, *cpyofpath = NULL, *tokenizedstr = NULL;
	char *buffer = malloc(sizeof(char) * 1024);

	if (cmd == NULL || buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		strcpy(buffer, cmd);
		return (buffer);
	}
	dir_topath = getenv("PATH");
	cpyofpath = strdup(dir_topath);
	if (cpyofpath == NULL || dir_topath == NULL)
	{
		free(buffer);
		return (NULL);
	}
	tokenizedstr = strtok(cpyofpath, ":");
	if (tokenizedstr == NULL)
	{
		free(buffer), free(cpyofpath);
		return (NULL);
	}
	while (tokenizedstr != NULL)
	{
		strcpy(buffer, tokenizedstr), strcat(buffer, "/"), strcat(buffer, cmd);
		if (access(buffer, X_OK) == 0)
		{
			free(cpyofpath);
			return (buffer);
		}
		tokenizedstr = strtok(NULL, ":");
	}
	free(cpyofpath), free(buffer);
	return (NULL);
}
