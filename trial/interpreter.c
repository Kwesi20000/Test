#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Main - entry point
 *
 * @command line interpreter
 *
 * Return: Always 0
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	size_t read;
	pid_t child_pid;
	int status;

	while (1)

	{
		printf("(>$)");

		read = getline(&line, &len, stdin);

		if  (read == -1)
		{
			if (isatty(STSIN_FILENO))
				printf("\n");
			break;
		}

		if  (line[read - 1] == '\n')
			line[read - 1] = '\0';


		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			return (EXIT_FAILURE);
		}
		else 
		{
			wait(&status);
		}
	}

	free(line);
	return (EXIT_SUCCESS);
}
