#include "main.h"

/**
 * checkBuiltIns - validates if command is builtin and executes
 * @init: input init
 * Return: 1 if found, 0 if not
 */
int checkBuiltIns(shellMaker *init)
{
	register int i = 0;
	type_b getBuiltIns[] = {
		{"exit", exitFunc},
		{"env", envFunc},
		{"history", historyFunc},
		{"alias", aliasFunc},
		{"cd", cdFunc},
		{"setenv", setenvFunc},
		{"unsetenv", unsetenvFunc},
		{"help", helpFunc},
		{NULL, NULL}
	};

	while (getBuiltIns[i].command)
	{
		if (_strcmp(init->args[0], getBuiltIns[i].command) == 0)
		{
			getBuiltIns[i].func(init);
			freeArgsAndBuffer(init);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * exitFunc - exits the application
 * @init: input init
 * Return: 1 on success, 0 on failure
 */
int exitFunc(shellMaker *init)
{
	register int argCount, exitStatus;

	argCount = countArgs(init->args);
	if (argCount == 1)
	{
		freeMem(init);
		if (init->processErrorStatus)
			exit(init->processErrorStatus);
		exit(EXIT_SUCCESS);
	}
	else if (argCount > 1)
	{
		exitStatus = _atoi(init->args[1]);
		if (exitStatus == -1)
		{
			errno = EILLEGAL;
			init->processErrorStatus = 2;
			errorHandler(init);
			return (0);
		}
		freeMem(init);
		exit(exitStatus);
	}
	return (1);
}

/**
 * historyFunc - displays command history
 * @init: input init
 * Return: 1 on success, 0 on failure
 */
int historyFunc(shellMaker *init)
{
	char *str = "Currently in development\n";

	(void)init;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * aliasFunc - displays local aliases
 * @init: input init
 * Return: 1 on success, 0 on failure
 */
int aliasFunc(shellMaker *init)
{
	char *str = "Currently in development\n";

	(void)init;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}
