#include "main.h"

/**
 * main - entry point for simple shell
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
	shellMaker init;

if (argc)
{
initializeSetter(&init);
init.shellName = argv[0];
start(&init);
}
return (0);
}

/**
 * initializeSetter - initialize member values for shellMaker struct
 * @init: input init
 * Return: init with initialized members
 */
shellMaker *initializeSetter(shellMaker *init)
{
	init->args = NULL;
	init->shellName = NULL;
	init->env = convertToLL(environ);
	init->envArr = NULL;
	init->buffer = NULL;
	init->path = _getenv("PATH", environ);
	init->actualPath = NULL;
	init->lineCounter = 0;
	init->processErrorStatus = 0;
	return (init);
}

