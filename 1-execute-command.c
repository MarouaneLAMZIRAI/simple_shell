#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 32

/**
 * execute_command - Execute the specified command line
 * @command_line: The command line to be executed
 */
void execute_command(char *command_line)
{
	pid_t pid;
	char *args[MAX_ARGS];
	char *token;
	int i = 0;

	token = strtok(command_line, " ");

	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}

	args[i] = NULL;
	if (args[0] == NULL)
	{
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, NULL);
		perror(args[0]);
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	else
	{
		perror("fork");
		exit(1);
	}
}
