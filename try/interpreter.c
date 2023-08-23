#include "shell.h"

int main(void) {
    char *command;

    while (1) {
        prompt_user();
        command = read_input();

        if (command == NULL)
            break;

        execute_command(command);
    }

    return EXIT_SUCCESS;
}
