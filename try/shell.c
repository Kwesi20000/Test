#include "shell.h"

/**
 * main - Entry point for the custom shell.
 *
 * Description:
 * This function initializes the shell, reads input from the user, parses it,
 * and executes commands until the user exits.
 *
 * Return: Always returns 0.
 */
int main(void)
{
    char *line;
    int argc;
    char *args[64];  /* Adjust the array size as needed */

    while (1)
    {
        prompt_user();
        line = read_input();

        if (line == NULL)
        {
            /* Handle end of input (Ctrl+D) */
            break;
        }

        tokenize_input(line, args, &argc);

        if (argc > 0)
        {
            if (strcmp(args[0], "exit") == 0)
            {
                free(line);
                exit(EXIT_SUCCESS);
            }

            /* Check if the command contains a '/' (indicating a path) or not */
            if (strchr(args[0], '/') != NULL)
            {
                if (execute_command_path(args[0]) != 0)
                {
                    fprintf(stderr, "Error executing command: %s\n", args[0]);
                }
            }
            else
            {
                if (execute_command_arg(args) != 0)
                {
                    fprintf(stderr, "Error executing command: %s\n", args[0]);
                }
            }
        }

        free(line);
    }

    return (0);
}

