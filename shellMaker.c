#include "main.h"

/**
 * start - simple shell
 * @init: input init
 */
void start(shellMaker *init)
{
	while (1)
	{
		checkStdin(init);
		if (splitString(init) == 0)
			continue;
		if (checkBuiltIns(init) == 1)
			continue;
		pathCheck(init);
		forkAndExecute(init);
	}
}

/**
 * checkStdin - check stdin and retrieves next line; handles
 * prompt display
 * @init: input init
 */
void checkStdin(shellMaker *init)
{
	register int len;
	size_t bufferSize = 0;
	char *ptr, *ptr2;

	init->args = NULL;
	init->envArr = NULL;
	init->lineCounter++;
	if (isatty(STDIN_FILENO))
		displayPrompt();
	len = getline(&init->buffer, &bufferSize, stdin);
	if (len == EOF)
	{
		freeMem(init);
		if (isatty(STDIN_FILENO))
			displayNewLine();
		if (init->processErrorStatus)
			exit(init->processErrorStatus);
		exit(EXIT_SUCCESS);

	}
	ptr = _strchr(init->buffer, '\n');
	ptr2 = _strchr(init->buffer, '\t');
	if (ptr || ptr2)
		putNullByte(init->buffer, len - 1);
	stripComments(init->buffer);
}

/**
 * stripComments - remove comments from input string
 * @str: input string
 * Return: length of remaining string
 */
void stripComments(char *str)
{
	register int i = 0;
	int notFirst = 0;

	while (str[i])
	{
		if (i == 0 && str[i] == '#')
		{
			putNullByte(str, i);
			return;
		}
		if (notFirst)
		{
			if (str[i] == '#' && str[i - 1] == ' ')
			{
				putNullByte(str, i);
				return;
			}
		}
		i++;
		notFirst = 1;
	}
}

/**
 * forkAndExecute - fork current init and execute processes
 * @init: input init
 */
void forkAndExecute(shellMaker *init)
{
	int status;
	pid_t f1 = fork();

	convertLListtoArr(init);
	if (f1 == -1)
	{
		perror("error\n");
		freeMem(init);
		freeArgs(init->envArr);
		exit(1);
	}
	if (f1 == 0)
	{
		if (execve(init->actualPath, init->args, init->envArr) == -1)
		{
			errorHandler(init);
			freeMem(init);
			freeArgs(init->envArr);
			if (errno == ENOENT)
				exit(127);
			if (errno == EACCES)
				exit(126);
		}
	} else
	{
		wait(&status);
		if (WIFEXITED(status))
			init->processErrorStatus = WEXITSTATUS(status);
		freeArgsAndBuffer(init);
		freeArgs(init->envArr);
	}
}

/**
 * convertLListtoArr - convert linked list to array
 * @init: input init
 */
void convertLListtoArr(shellMaker *init)
{
	register int i = 0;
	size_t count = 0;
	char **envArr = NULL;
	l_list *tmp = init->env;

	count = l_list_len(init->env);
	envArr = malloc(sizeof(char *) * (count + 1));
	if (!envArr)
	{
		perror("Malloc failed\n");
		exit(1);
	}
	while (tmp)
	{
		envArr[i] = _strdup(tmp->string);
		tmp = tmp->next;
		i++;
	}
	envArr[i] = NULL;
	init->envArr = envArr;
}
