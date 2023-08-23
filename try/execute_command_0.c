#include "shell.h"

int execute_command_arg(char *args[]) {
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1) {
        perror("Error");
        return EXIT_FAILURE;
    }

    if (child_pid == 0) {
        /*Child process*/
        if (execvp(args[0], args) == -1) {
            perror("Error");
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process*/
        wait(&status);
    }

    return EXIT_SUCCESS;
}
