#include "main.h"

/**
 * _getenv - retrieves env variable that matches input string
 * @input: input string
 * @environ: local environmental variables
 * Return: string of env variable
 */
char *_getenv(char *input, char **environ)
{
	register int i = 0;
	char *tok, *right;

	while (environ[i])
	{
		tok = _strtok(environ[i], "=");
		if (_strcmp(tok, input) == 0)
		{
			right = _strtok(NULL, "=");
			return (right);
		}
		i++;
	}
	return (NULL);
}

/**
 * envFunc - prints the environment
 * @init: input init
 * Return: Always 1
 */
int envFunc(shellMaker *init)
{
	printList(init->env);
	return (1);
}

/**
 * setenvFunc - adds env variable if it does not exist;
 * modify env variable if it does
 * @init: input init
 * Return: Always 1
 */
int setenvFunc(shellMaker *init)
{
	register int index, len;
	static char buffer[BUFSIZE];

	if (countArgs(init->args) != 3)
	{
		errno = EWSIZE;
		errorHandler(init);
		return (1);
	}
	len = _strlen(init->args[1]) + _strlen(init->args[2]) + 2;
	_strcat(buffer, init->args[1]);
	_strcat(buffer, "=");
	_strcat(buffer, init->args[2]);
	putNullByte(buffer, len - 1);
	index = searchNode(init->env, init->args[1]);
	if (index == -1)
	{
		addNodeEnd(&init->env, buffer);
		putNullByte(buffer, 0);
		return (1);
	}
	deleteNodeAtIndex(&init->env, index);
	addNodeAtIndex(&init->env, index, buffer);
	putNullByte(buffer, 0);
	return (1);
}

/**
 * unsetenvFunc - deletes env variable if exists;
 * will only accept valid variables names
 * @init: input init
 * Return: Always 1
 */
int unsetenvFunc(shellMaker *init)
{
	register int foundVar, i = 1;
	int foundMatch = 0;

	while (init->args[i])
	{
		if (_isalpha(init->args[i][0]) || init->args[i][0] == '_')
		{
			foundVar = searchNode(init->env, init->args[i]);
			if (foundVar > -1)
			{
				deleteNodeAtIndex(&init->env, foundVar);
				foundMatch = 1;
			}
		}
		i++;
	}
	if (foundMatch == 0)
	{
		errno = ENOSTRING;
		errorHandler(init);
	}
	return (1);
}

/**
 * _isalpha - checks if c is an alphabetic character
 * @c: potential alphabetical value
 * Return: if c is a letter, returns 1. Otherwise, return 0.
 */
int _isalpha(int c)
{
	if (c > 64 && c < 91)
		return (1);
	else if (c > 96 && c < 123)
		return (1);
	else
		return (0);
}
