#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - Simple shell program
 *
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t child_pid;
    int status;

    while (1)
    {
        printf("($) ");
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        child_pid = fork();
        if (child_pid == -1)
        {
            perror("Error");
            return (EXIT_FAILURE);
        }
        if (child_pid == 0)
        {
            char *args[2]; // Assuming a simple command with no arguments

            args[0] = line;
            args[1] = NULL;

            execve(line, args, NULL); // Execute the command
            perror("Error");
            free(line);
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(&status);
        }
    }

    free(line);
    return (EXIT_SUCCESS);
}

