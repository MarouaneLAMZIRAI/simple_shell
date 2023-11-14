#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

/**
 * main - Entry point of the program
 *
 * Return: Always 0 (success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		print_prompt();
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);

			break;
		}

		if (read > 1)
		{
			line[read - 1] = '\0'; /* Remove newline character */

			if (fork() == 0)
			{
				execute_command(line);
				exit(0);
			}
			else
			{
				wait(NULL);
			}
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
		}
	}

	free(line);
	return (0);
}
