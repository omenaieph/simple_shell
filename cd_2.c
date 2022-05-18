#include "main.h"

/**
 * updateOld - updates OLDPWD to current PWD
 * @init: input init
 * Return: index in linked list of PWD on success -
 * If PWD or OLDPWD does not exist in environ vars,
 * return -1
 */
int updateOld(shellMaker *init)
{
	register int pwdIndex = 0, index = 0;
	static char old[BUFSIZE];
	char *current = NULL;

	_strcat(old, "OLD");
	pwdIndex = searchNode(init->env, "PWD");
	if (pwdIndex == -1)
	{
		return (-1);
	}
	current = getNodeAtIndex(init->env, pwdIndex);
	_strcat(old, current);
	putNullByte(old, _strlen(current) + 4);
	free(current);
	index = searchNode(init->env, "OLDPWD");
	if (index == -1)
	{
		return (-1);
	}
	deleteNodeAtIndex(&init->env, index);
	addNodeAtIndex(&init->env, index, old);
	putNullByte(old, 0);
	return (pwdIndex);
}

/**
 * updateCur - updates PWD to accurately reflect current directory
 * @init: input init
 * @index: index in linked list of where to insert PWD env var
 * Return: 1 on success, 0 on failure
 */
int updateCur(shellMaker *init, int index)
{
	static char tmp[BUFSIZE], cwd[BUFSIZE];

	getcwd(tmp, BUFSIZE);
	_strcat(cwd, "PWD=");
	_strcat(cwd, tmp);
	if (index > -1)
	{
		deleteNodeAtIndex(&init->env, index);
		addNodeAtIndex(&init->env, index, cwd);
	} else
		addNodeAtIndex(&init->env, 0, cwd);
	putNullByte(tmp, 0);
	putNullByte(cwd, 0);
	return (1);
}
