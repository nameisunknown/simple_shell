#include "shell.h"

char *_findpath(char *cmd)
{
	char *dir_topath = NULL;
	char *cpyofpath = NULL;
	char **tokenizedstr = malloc(sizeof(char *) * 1024);
	char *buffer = malloc(sizeof(char) * 1024);

	if (cmd == NULL || tokenizedstr == NULL || buffer == NULL)
	{
		free_entities(buffer, tokenizedstr);
		return (NULL);
	}

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		strcpy(buffer, cmd);
		free(tokenizedstr);
		return (buffer);
	}

	dir_topath = getenv("PATH");

	if (dir_topath == NULL)
	{
		free_entities(buffer, tokenizedstr);
		return (NULL);
	}
	cpyofpath = strdup(dir_topath);

	if (cpyofpath == NULL)
	{
		free_entities(buffer, tokenizedstr);
		return (NULL);
	}

	*tokenizedstr = strtok(cpyofpath, ":");

	if (tokenizedstr == NULL)
	{
		free(buffer);
		free(cpyofpath);
		return (NULL);
	}

	while (*tokenizedstr != NULL)
	{
		strcpy(buffer, *tokenizedstr);
		strcat(buffer, "/");
		strcat(buffer, cmd);

		if (access(buffer, X_OK) == 0)
		{
			free_entities(cpyofpath, tokenizedstr);
			return (buffer);
		}
		*tokenizedstr = strtok(NULL, ":");
	}
	free(cpyofpath);
	free_entities(buffer, tokenizedstr);
	return (NULL);
}

void free_entities(char *buffer, char **tokenizedstr)
{
	free(buffer);
	free(tokenizedstr);
}
