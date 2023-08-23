#include "shell.h"

extern char **environ;

int execute_command_path(char *command) {
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1) {
        perror("Error");
        return EXIT_FAILURE;
    }

    if (child_pid == 0) {
        /* Child process*/
        char *command_path = get_command_path(command);
        if (command_path == NULL) {
            fprintf(stderr, "Command not found: %s\n", command);
            free(command);
            exit(EXIT_FAILURE);
        }

        if (execve(command_path, &command, environ) == -1) {
            perror("Error");
            free(command);
            free(command_path);
            exit(EXIT_FAILURE);
        }
    } else {
        /*Parent process*/
        wait(&status);
    }

    free(command);
    return EXIT_SUCCESS;
}
