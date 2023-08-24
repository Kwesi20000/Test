#include "shell.h"

void shell_loop(void)
{
char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("($) ");
        read = getline(&line, &len, stdin);

        if (read == -1)  /* Handle end of file (Ctrl+D) */
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        char *command = strtok(line, " ");
        if (command == NULL)
            continue;

        if (strcmp(command, "exit") == 0) {
            free(line);
            exit(EXIT_SUCCESS);
        }

        execute_command(command);
    }

    free(line);
}

