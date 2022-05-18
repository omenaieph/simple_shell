#include "main.h"

/**
 * splitString - splits string into an array of strings
 * separated by spaces
 * @init: input init
 * Return: 1 if able to split, 0 if not
 */
int splitString(shellMaker *init)
{
	register unsigned int i = 0;
	char *tok, *cpy;

	if (countWords(init->buffer) == 0)
	{
		init->args = NULL;
		free(init->buffer);
		return (0);
	}
	init->args = malloc((countWords(init->buffer) + 1) * sizeof(char *));
	cpy = _strdup(init->buffer);
	tok = _strtok(cpy, " ");
	while (tok)
	{
		init->args[i] = _strdup(tok);
		tok = _strtok(NULL, " ");
		i++;
	}
	init->args[i] = NULL;
	free(cpy);
	return (1);
}

/**
 * countWords - count number of words in a string
 * @str: input string
 * Return: number of words
 */
unsigned int countWords(char *str)
{
	register int words = 0;
	int wordOn = 0;

	while (*str)
	{
		if (isSpace(*str) && wordOn)
			wordOn = 0;
		else if (!isSpace(*str) && !wordOn)
		{
			wordOn = 1;
			words++;
		}
		str++;
	}
	return (words);
}

/**
 * isSpace - determines if char is a space
 * @c: input char
 * Return: 1 or 0
 */
int isSpace(char c)
{
	int ret = 0;

	if (c == ' ')
	{
		ret = 1;
	}
	return (ret);
}
