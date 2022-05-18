#include "main.h"

/**
 * helpAlias - instructions on how to exit
 * @init: input init
 * Return: Always 1
 */
int helpAlias(shellMaker *init)
{
	char str[] = "alias: alias\n\tNot supported in this version.\n";

	(void)init;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * helpCd - instructions on how to exit
 * @init: input init
 * Return: Always 1
 */
int helpCd(shellMaker *init)
{
	char str[192] = "cd: cd [destination]\n\t";
	char *str2 = "Change directory to target destination.\n\t";
	char *str3 = "If [destination] is ommitted, user will taken to home.\n\t";
	char *str4 = "If \"-\" is used as second argument, user will be taken to ";
	char *str5 = "last directory.\n";

	(void)init;
	_strcat(str, str2);
	_strcat(str, str3);
	_strcat(str, str4);
	_strcat(str, str5);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * helpSetenv - instructions on how to exit
 * @init: input init
 * Return: Always 1
 */
int helpSetenv(shellMaker *init)
{
	char str[186] = "setenv: setenv [var] [value]\n\t";
	char *str2 = "Set or update a variable in the environment.\n\n\t";
	char *str3 = "Creates a variable [var] with [value]. ";
	char *str4 = "If the [var] already exists in the environment, ";
	char *str5 = "the value is updated.\n";

	(void)init;
	_strcat(str, str2);
	_strcat(str, str3);
	_strcat(str, str4);
	_strcat(str, str5);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * helpUnsetenv - instructions on how to exit
 * @init: input init
 * Return: Always 1
 */
int helpUnsetenv(shellMaker *init)
{
	char str[116] = "unsetenv: unsetenv [var]\n\t";
	char *str2 = "Unset a variable in the environment.\n\n\t";
	char *str3 = "[var] is an existing variable in the environment.\n";

	(void)init;
	_strcat(str, str2);
	_strcat(str, str3);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * helpHelp - instructions on how to exit
 * @init: input init
 * Return: Always 1
 */
int helpHelp(shellMaker *init)
{
	char str[129] = "help: help [built-in]\n\t";
	char *str2 = "Display information about built-in commands.\n\n\t";
	char *str3 = "If [built-in] is not specified, print a list of built-ins.\n";

	(void)init;
	_strcat(str, str2);
	_strcat(str, str3);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}
