#include "shell.h"

/**
 * shellLoop - Main shell loop.
 * @info: The parameter and return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int shellLoop(info_t *info, char **av)
{
	ssize_t ret = 0;
	int builtinResult = 0;

	while (ret != -1 && builtinResult != -2)
	{
		clearInfoStruct(info);
		if (isInteractive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		ret = getInput(info);
		if (ret != -1)
		{
			setInfoStruct(info, av);
			builtinResult = findBuiltin(info);
			if (builtinResult == -1)
				findCommand(info);
		}
		else if (isInteractive(info))
			_putchar('\n');
		freeInfoStruct(info, 0);
	}
	writeHistory(info);
	freeInfoStruct(info, 1);
	if (!isInteractive(info) && info->status)
		exit(info->status);
	if (builtinResult == -2)
	{
		if (info->errorNum == -1)
			exit(info->status);
		exit(info->errorNum);
	}
	return (builtinResult);
}

/**
 * findBuiltin - Finds a builtin command.
 * @info: The parameter and return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         2 if builtin signals exit()
 */
int findBuiltin(info_t *info)
{
	int i, builtinResult = -1;
	builtinTable builtinTable[] = {
		{"exit", myExit},
		{"env", myEnv},
		{"help", myHelp},
		{"history", myHistory},
		{"setenv", mySetenv},
		{"unsetenv", myUnsetenv},
		{"cd", myCd},
		{"alias", myAlias},
		{NULL, NULL}
	};

	for (i = 0; builtinTable[i].type; i++)
	{
		if (_strcmp(info->argv[0], builtinTable[i].type) == 0)
		{
			info->lineCount++;
			builtinResult = builtinTable[i].func(info);
			break;
		}
	}
	return (builtinResult);
}

/**
 * findCommand - Finds a command in PATH.
 * @info: The parameter and return info struct.
 *
 * Return: void.
 */
void findCommand(info_t *info)
{
	char *path = NULL;
	int i, countNonDelim = 0;

	info->path = info->argv[0];
	if (info->lineCountFlag == 1)
	{
		info->lineCount++;
		info->lineCountFlag = 0;
	}
	for (i = 0; info->arg[i]; i++)
	{
		if (!isDelimiter(info->arg[i], " \t\n"))
			countNonDelim++;
	}
	if (!countNonDelim)
		return;

	path = findPath(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkCommand(info);
	}
	else
	{
		if ((isInteractive(info) || _getenv(info, "PATH=") ||
					info->argv[0][0] == '/')
			&& isCmd(info, info->argv[0]))
			forkCommand(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printError(info, "not found\n");
		}
	}
}

/**
 * forkCommand - Forks an exec thread to run a command.
 * @info: The parameter and return info struct.
 *
 * Return: void.
 */
void forkCommand(info_t *info)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{
		perror("Error:");
		return;
	}
	if (childPid == 0)
	{
		if (execve(info->path, info->argv, getEnvironment(info)) == -1)
		{
			freeInfoStruct(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printError(info, "Permission denied\n");
		}
	}
}

