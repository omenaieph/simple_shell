#include "main.h"

/**
 * checkEdgeCases - helper func for check path to check edge cases
 * @init: input init
 * Return: 1 if found, 0 if not
 */
int checkEdgeCases(shellMaker *init)
{
	char *copy;
	struct stat st;

	copy = _strdup(init->path);
	if (!copy)
	{
		init->actualPath = init->args[0];
		free(copy);
		return (1);
	}
	if (*copy == ':' && stat(init->args[0], &st) == 0)
	{
		init->actualPath = init->args[0];
		free(copy);
		return (1);
	}
	free(copy);
	return (0);
}
/**
 * pathCheck - searches $PATH for directory of command
 * @init: initial
 * Return: 1 if found, 0 if not
 */

int pathCheck(shellMaker *init)
{
	register int len;
	static char buffer[BUFSIZE];
	struct stat st;
	char *tok, *copy, *delim = ":", *tmp;
	int inLoop = 0;

	if (checkEdgeCases(init))
		return (1);
	copy = _strdup(init->path);
	tok = _strtok(copy, delim);
	while (tok)
	{
		tmp = inLoop ? tok - 2 : tok;
		if (*tmp == 0 && stat(init->args[0], &st) == 0)
		{
			init->actualPath = init->args[0];
			free(copy);
			return (1);
		}
		len = _strlen(tok) + _strlen(init->args[0]) + 2;
		_strcat(buffer, tok);
		_strcat(buffer, "/");
		_strcat(buffer, init->args[0]);
		putNullByte(buffer, len - 1);
		if (stat(buffer, &st) == 0)
		{
			free(copy);
			init->actualPath = buffer;
			return (1);
		}
		putNullByte(buffer, 0);
		tok = _strtok(NULL, delim);
		inLoop = 1;
	}
	init->actualPath = init->args[0];
	free(copy);
	return (0);
}
