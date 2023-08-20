#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

int main(void)
{
    char input[MAX_INPUT_SIZE];
    pid_t child_pid;
    int status;

    while (1)
    {
        printf("($) ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            // Handle end of file (Ctrl+D)
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }

        // Remove trailing newline, if present
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
            input[len - 1] = '\0';

        if (strcmp(input, "exit") == 0)
        {
            // Exit the shell if the user enters "exit"
            break;
        }

        child_pid = fork();
        if (child_pid == -1)
        {
            perror("Error");
            return EXIT_FAILURE;
        }

        if (child_pid == 0)
        {
            char *args[] = {input, NULL};
            execvp(input, args);

            // If execvp fails, print an error and exit
            perror("Error");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process waits for the child
            waitpid(child_pid, &status, 0);

            // Check if the child process exited normally
            if (WIFEXITED(status))
            {
                printf("Child exited with status %d\n", WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status))
            {
                printf("Child terminated by signal %d\n", WTERMSIG(status));
            }
        }
    }

    return EXIT_SUCCESS;
}

