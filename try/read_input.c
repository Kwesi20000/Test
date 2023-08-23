#include "shell.h"

char *read_input(void) 
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, stdin);

    if (read == -1)
    {  /* Handle end of file (Ctrl+D) */
        if (isatty(STDIN_FILENO))
            printf("\n");
        free(line);
        return NULL;
    }

    if (line[read - 1] == '\n')
        line[read - 1] = '\0';

    return line;
}
