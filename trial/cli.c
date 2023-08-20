#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

        if (read == -1)  // Handle end of file (Ctrl+D)
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
            if (execve(line, NULL, environ) == -1)
            {
                perror("Error");
                free(line);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(&status);
        }
    }

    free(line);
    return (EXIT_SUCCESS);
}

