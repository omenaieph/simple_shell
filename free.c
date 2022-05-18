#include "main.h"

/**
 * freeMem - frees init shellMaker members
 * @init: input init
 */
void freeMem(shellMaker *init)
{
	if (init->env)
		freeList(init->env);
	if (init->args)
		freeArgs(init->args);
	if (init->buffer)
		free(init->buffer);
}

/**
 * freeArgsAndBuffer - frees args and buffer
 * @init: input init
 */
void freeArgsAndBuffer(shellMaker *init)
{
	freeArgs(init->args);
	free(init->buffer);
}

/**
 * freeList - frees a linked list
 * @head: double pointer to head of list
 */
void freeList(l_list *head)
{
	l_list *current;
	l_list *tmp;

	if (!head)
		return;
	current = head;
	while (current)
	{
		tmp = current;
		current = tmp->next;
		free(tmp->string);
		free(tmp);
	}
	head = NULL;
}

/**
 * freeArgs - helper func that frees double pointer arg
 * @args: array of char pointers
 */
void freeArgs(char **args)
{
	register uint i = 0;

	while (args[i])
		free(args[i++]);
	free(args);
}
