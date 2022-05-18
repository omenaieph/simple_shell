#include "main.h"

/**
 * helpFunc - retrieves instruction on how to use builtin
 * @init: input init
 * Return: Always 1
 */
int helpFunc(shellMaker *init)
{
	type_b help_arr[] = {
		{"exit", helpExit},
		{"env", helpEnv},
		{"history", helpHistory},
		{"alias", helpAlias},
		{"cd", helpCd},
		{"setenv", helpSetenv},
		{"unsetenv", helpUnsetenv},
		{"help", helpHelp},
		{NULL, NULL}
	};
	register int i = 0, j = 1, argCount = countArgs(init->args);
	int foundCommand = 0;

	if (argCount == 1)
		return (displayHelpMenu());
	while (j < argCount)
	{
		i = 0;
		while (help_arr[i].command)
		{
			if (_strcmp(init->args[j], help_arr[i].command) == 0)
			{
				foundCommand = 1;
				help_arr[i].func(init);
				break;
			}
			i++;
		}
		j++;
	}
	if (foundCommand == 0)
	{
		errno = ENOBUILTIN;
		errorHandler(init);
	}
	return (1);
}

/**
 * displayHelpMenu - displays available help options
 * Return: Always 1
 */
int displayHelpMenu(void)
{
	char str[81] = "Type help [built-in]\n\nIncluded built-ins:";
	char *str2 = "\n\n\texit\n\tenv\n\tcd\n\tsetenv\n\tunsetenv\n\thelp\n";

	_strcat(str, str2);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}


/**
 * helpExit - instructions on how to exit
 * @init: input init
 * Return: Always 1
 */
int helpExit(shellMaker *init)
{
	char str[82] = "exit: exit [n]\n\tExit the shell.\n\n\t";
	char *str2 = "Exit with a status of n, or if n is omitted, 0.\n";

	(void)init;
	_strcat(str, str2);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * helpEnv - instructions on how to exit
 * @init: input init
 * Return: Always 1
 */
int helpEnv(shellMaker *init)
{
	char str[] = "env: env\n\tPrint the environment.\n";

	(void)init;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * helpHistory - instructions on how to exit
 * @init: input init
 * Return: Always 1
 */
int helpHistory(shellMaker *init)
{
	char str[] = "history: history\n\tNot supported in this version.\n";

	(void)init;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}
