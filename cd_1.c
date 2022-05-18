#include "main.h"

/**
 * cdFunc - execute cd builtin
 * @init: input init
 * Return: 1 on success, 0 on failure
 */
int cdFunc(shellMaker *init)
{
	register uint count = 0;
	int ableToChange = 0;

	count = countArgs(init->args);
	if (count == 1)
		ableToChange = cdToHome(init);
	else if (count == 2 && _strcmp(init->args[1], "-") == 0)
		ableToChange = cdToPrevious(init);
	else
		ableToChange = cdToCustom(init);
	if (ableToChange)
		updateEnviron(init);
	return (1);
}

/**
 * cdToHome - change directory to home
 * @init: input init
 * Return: 1 on success, 0 on failure
 */
int cdToHome(shellMaker *init)
{
	register int i;
	char *str, *ptr;

	i = searchNode(init->env, "HOME");
	if (i == -1)
	{
		return (1);
	}
	str = getNodeAtIndex(init->env, i);
	ptr = _strchr(str, '=');
	ptr++;
	chdir(ptr);
	free(str);
	return (1);
}

/**
 * cdToPrevious - change directory to previous directory -
 * address is found in OLDPWD env var
 * @init: input init
 * Return: 1 on success, 0 on failure
 */
int cdToPrevious(shellMaker *init)
{
	register int i;
	char *str, *ptr;
	char *current = NULL;

	current = getcwd(current, 0);
	i = searchNode(init->env, "OLDPWD");
	if (i == -1)
	{
		chdir(current);
		write(STDOUT_FILENO, current, _strlen(current));
		displayNewLine();
		return (1);
	}
	str = getNodeAtIndex(init->env, i);
	ptr = _strchr(str, '=');
	ptr++;
	chdir(ptr);
	write(STDOUT_FILENO, ptr, _strlen(ptr));
	displayNewLine();
	free(str);
	return (1);
}

/**
 * cdToCustom - change directory to what user inputs in
 * @init: input init
 * Return: 1 on success, 0 on failure
 */
int cdToCustom(shellMaker *init)
{
	register int changeStatus;

	changeStatus = chdir(init->args[1]);
	if (changeStatus == -1)
	{
		errno = EBADCD;
		errorHandler(init);
		return (0);
	}
	return (1);
}

/**
 * updateEnviron - change environmental variables
 * @init: input init
 * Return: 1 on success 0 on failure
 */
int updateEnviron(shellMaker *init)
{
	register int i;

	i = updateOld(init);
	updateCur(init, i);
	return (1);
}
