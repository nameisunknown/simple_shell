#include "shell.h"

/**
 * handleError - prints err msg and exit
 *
 * @void: does not take in parameter
 */

void handleError(void)
{
	perror("./shell");
	exit(EXIT_FAILURE);
}

/**
 * main - Entry point to program
 *
 * @void: takes no argument
 * Return: returns 0 upon success
 */
int main(void)
{
	char *readString = NULL, **tokenizedArgs = NULL, *pathHolder = NULL;
	size_t readStringSize = 0;
	ssize_t noOfValuesInStringRead = 0;
	pid_t forkedChildPid;
	int status;

	while (true)
	{
		printf("$ ");
		noOfValuesInStringRead = getline(&readString, &readStringSize, stdin);
		if (noOfValuesInStringRead == -1)
			break;
		readString[noOfValuesInStringRead - 1] = '\0';
		tokenizedArgs = brkStr(readString, " \n\t");
		pathHolder = _findpath(tokenizedArgs[0]);
		if (pathHolder == NULL || (access(pathHolder, X_OK)) == -1)
		{
			if (errno == EACCES)
			{
				perror("Permission denied");
				continue;
			}
			perror("ERROR: not found\n");
			continue;
		}
		forkedChildPid = fork();
		if (forkedChildPid == -1)
			handleError();
		if (forkedChildPid == 0)
		{
			if (execve(pathHolder, tokenizedArgs, NULL) == -1)
				handleError();
		}
		waitpid(forkedChildPid, &status, 0);
		free(readString), free(tokenizedArgs), free(pathHolder);
		readString = NULL, tokenizedArgs = NULL;
	}
	free(readString);
	return (0);
}

/**
 * brkStr - breaks a group of string to single str entity
 *
 * @strEntered: string to be broken of type char pointer
 * @separator: delimiting factor to use to brk str entered
 * Return: a double pointer containing the broken strings
 */

char **brkStr(char *strEntered, char *separator)
{
	int itemPresentInStr = 0;
	char **strReturned = NULL;
	char *strCollected = NULL;
	char *cpyOfStrEntered = NULL;
	int counter = 0;

	if (strEntered == NULL)
		exit(EXIT_FAILURE);

	strCollected = strtok(strEntered, separator);
	cpyOfStrEntered = strdup(strEntered);

	while (strCollected != NULL)
	{
		itemPresentInStr++;
		strCollected = strtok(NULL, separator);
	}
	strReturned = malloc((itemPresentInStr + 1) * sizeof(char *));
	strCollected = strtok(cpyOfStrEntered, separator);

	while (strCollected != NULL)
	{
		strReturned[counter] = malloc(strlen(strCollected + 1) * sizeof(char));
		strcpy(strReturned[counter], strCollected);
		strCollected = strtok(NULL, separator);
		counter++;
	}
	strReturned[counter] = NULL;
	free(cpyOfStrEntered);
	return (strReturned);
}
