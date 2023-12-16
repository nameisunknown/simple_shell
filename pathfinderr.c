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
	char *buffer;

	if (cmd == NULL)
		return (NULL);
	buffer = malloc(sizeof(char) * (strlen(cmd) + 800));
	if (buffer == NULL)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		strcpy(buffer, cmd);
		return (buffer);
	}
	dir_topath = getenv("PATH");
	if (dir_topath == NULL)
		return (NULL);
	cpyofpath = strdup(dir_topath);
	if (cpyofpath == NULL)
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
