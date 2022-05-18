#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execute - executes the command
 * @forked: number of child processes
 * Return: Always 0, -1 on error.
 */
int execute(void)
{
    int waitTime;
	int ps = 0;
    pid_t my_pid, my_ppid, child_pid;
    char *argv[] = {"/bin/ls", "-l", NULL};

    while (ps != 5)
    {
        child_pid = fork();
        printf("fork num: %i\n",child_pid);
        if (child_pid == -1)
        {
            perror("Error");
            return (1);
        }
        else if (child_pid == 0)
        {
            if (execve(argv[0],argv,NULL) == -1)
            {
                perror("Error");
            }
        }
        else
        {
            sleep(3);
            wait(&waitTime);
            ps += 1;
        }

        my_pid = getpid();
        my_ppid = getppid();
        printf("pid: %u, parentPid: %u\n",my_pid, my_ppid);
    }
}

/**
 * main - fork & wait example
 *
 * Return: Always 0.
 */
int main(void)
{

	execute();
	return (0);
}
