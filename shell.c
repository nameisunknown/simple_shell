#include "shell.h"
#include "globals.h"

char *_programName;
int _exitStatus;
int _counter;

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
 * @argc: count of arg entered
 * @argv: pointer carrying the arg entered
 * Return: returns 0 upon success
 */

int main(int argc, char **argv)
{
	char *readString = NULL, **tokenizedArgs = NULL, *pathHolder = NULL;
	size_t readStringSize = 0;
	ssize_t noOfValuesInStringRead = 0;

	(void) (argc);
	_programName = argv[0];
	while (true)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		noOfValuesInStringRead = getline(&readString, &readStringSize, stdin);
		if (noOfValuesInStringRead == -1)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			break;
		}
		readString[noOfValuesInStringRead - 1] = '\0';
		tokenizedArgs = brkStr(readString, " \n\t");
		pathHolder = _findpath(tokenizedArgs[0]);
		if (pathHolder == NULL)
		{
			_perror("%s: %d: %s: not found\n",
					_programName, _counter, tokenizedArgs[0]), _exitStatus = 127;
			free_tokenizedArgs(tokenizedArgs);
			continue;
		}
		_exitStatus = create_fork(pathHolder, tokenizedArgs, readString);
		free_tokenizedArgs(tokenizedArgs), free(pathHolder);
	}
	free(readString);
	return (_exitStatus);
}

/**
 * create_fork - forks the child process
 *
 * @full_path: this is the full path
 * @tokenizedArgs: this is the tokenizedArgs
 * @readString: the string to be read
 * Return: exit status is returned
 */
int create_fork(char *full_path, char **tokenizedArgs, char *readString)
{
	pid_t forkedChildPid = fork();
	int status;

	if (forkedChildPid == -1)
		exit(1);
	if (forkedChildPid == 0)
	{
		if (execve(full_path, tokenizedArgs, NULL) == -1)
		{
			if (errno == EACCES)
			{
				_perror("%s: %d: %s: Permision denied\n",
						_programName, _counter, tokenizedArgs[0]);
				free_tokenizedArgs(tokenizedArgs);
				free(readString);
				free(full_path);
				exit(126);
			}
			else
			{
				_perror("%s: %d: %s: not found\n",
						_programName, _counter, tokenizedArgs[0]);
				free_tokenizedArgs(tokenizedArgs);
				free(readString);
				free(full_path);
				exit(127);
			}
			exit(1);
		}
	}
	else
	{
		wait(&status);
		status = WEXITSTATUS(status);
	}
	return (status);
}

/**
 * free_tokenizedArgs - free an array of tokenized pointers
 *
 * @toksArgs: An Array of pointers to be freed
 */

void free_tokenizedArgs(char *toksArgs[])
{
	int i = 0;

	while (toksArgs[i] != NULL)
	{
		free(toksArgs[i]);
		i++;
	}
	free(toksArgs[i]);
	free(toksArgs);
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

	cpyOfStrEntered = strdup(strEntered);
	strCollected = strtok(strEntered, separator);

	while (strCollected != NULL)
	{
		itemPresentInStr++;
		strCollected = strtok(NULL, separator);
	}
	strReturned = malloc((itemPresentInStr + 1) * sizeof(char *));
	strCollected = strtok(cpyOfStrEntered, separator);

	while (strCollected != NULL)
	{
		strReturned[counter] = malloc((strlen(strCollected) + 1) * sizeof(char));
		strcpy(strReturned[counter], strCollected);
		strCollected = strtok(NULL, separator);
		counter++;
	}
	strReturned[counter] = NULL;
	free(cpyOfStrEntered);
	return (strReturned);
}
