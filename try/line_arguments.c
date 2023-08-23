#include "shell.h"

int main(void) {
    char *line;
    char *args[64];
    int argc;

    while (1) {
        prompt_user();
        line = read_input();

        if (line == NULL)
            break;

        tokenize_input(line, args, &argc);
        if (argc > 0)
            execute_command_arg(args);

        free(line);
    }

    return EXIT_SUCCESS;
}
