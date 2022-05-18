#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>

/* ERRORS */
#define BUFSIZE 256
#define ENOSTRING 1106
#define EILLEGAL 227
#define EWSIZE 410
#define ENOBUILTIN 415
#define EBADCD 726

extern char **environ;

/**
 * struct linkedList - linked list data structure
 * @string: environ variable path name
 * @next: pointer to next node
 */
typedef struct linkedList
{
	char *string;
	struct linkedList *next;
} l_list;

/**
 * struct initialization - shellMakeruration of init settings
 * @env: linked list of local env variables
 * @envArr: array of env variables to put into execve
 * @args: array of argument strings
 * @buffer: string buffer of user input
 * @path: array of $PATH locations
 * @actualPath: string of path with correct prepended $PATH
 * @shellName: name of shellMaker (argv[0])
 * @lineCounter: counter of lines users have entered
 * @processErrorStatus: error status of last child process
 */
typedef struct initialization
{
    char **args;
    char *shellName;
	l_list *env;
	char **envArr;
	char *buffer;
	char *path;
	char *actualPath;
	unsigned int lineCounter;
	int processErrorStatus;
} shellMaker;

/**
 * struct builtInCommands - commands and functions associated with it
 * @command: input command
 * @func: output function
 */
typedef struct builtInCommands
{
	char *command;
	int (*func)(shellMaker *init);
} type_b;

/* main */
shellMaker *initializeSetter(shellMaker *init);

/* built_ins */
int checkBuiltIns(shellMaker *init);
int exitFunc(shellMaker *init);
int historyFunc(shellMaker *init);
int aliasFunc(shellMaker *init);

/* cd */
int cdFunc(shellMaker *);
int cdToHome(shellMaker *init);
int cdToPrevious(shellMaker *init);
int cdToCustom(shellMaker *init);
int updateEnviron(shellMaker *init);

/* cd2 */
int updateOld(shellMaker *init);
int updateCur(shellMaker *init, int index);

/* env */
int envFunc(shellMaker *init);
int setenvFunc(shellMaker *init);
int unsetenvFunc(shellMaker *init);
int _isalpha(int c);

/* help */
int helpFunc(shellMaker *init);
int displayHelpMenu(void);
int helpExit(shellMaker *init);
int helpEnv(shellMaker *init);
int helpHistory(shellMaker *init);

/* help2 */
int helpAlias(shellMaker *init);
int helpCd(shellMaker *biuld);
int helpSetenv(shellMaker *init);
int helpUnsetenv(shellMaker *init);
int helpHelp(shellMaker *init);

/* built_in_helpers*/
int countArgs(char **args);
int _atoi(char *s);

/* shellMaker */
void start(shellMaker *init);
void checkStdin(shellMaker *init);
void forkAndExecute(shellMaker *init);
void stripComments(char *str);
void convertLListtoArr(shellMaker *init);

/* _getenv */
char *_getenv(char *input, char **environ);

/* error_handler */
void errorHandler(shellMaker *init);
unsigned int countDigits(int num);
char *itoa(unsigned int num);
char *getErrorMessage();

/* shell_helpers */
void putNullByte(char *str, unsigned int index);
void displayPrompt(void);
void displayNewLine(void);
void sigintHandler(int sigint);

/* check_path */
int pathCheck(shellMaker *);
int checkEdgeCases(shellMaker *init);

/* split_string */
int splitString(shellMaker *init);
unsigned int countWords(char *s);
int isSpace(char c);

/* string_helpers1 */
int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);

/* string_helpers2 */
char *_strtok(char *str, char *delim);
int _strcspn(char *string, char *chars);
char *_strchr(char *s, char c);

/* llfuncs1 */
l_list *addNode(l_list **head, char *str);
l_list *addNodeEnd(l_list **head, char *str);
size_t printList(const l_list *h);
int searchNode(l_list *head, char *str);
size_t l_list_len(l_list *h);

/* llfuncs2 */
int deleteNodeAtIndex(l_list **head, unsigned int index);
l_list *convertToLL(char **array);
l_list *addNodeAtIndex(l_list **head, int index, char *str);
char *getNodeAtIndex(l_list *head, unsigned int index);

/* _realloc */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memcpy(char *dest, char *src, unsigned int n);

/* free */
void freeMem(shellMaker *init);
void freeArgsAndBuffer(shellMaker *init);
void freeArgs(char **args);
void freeList(l_list *head);

#endif
