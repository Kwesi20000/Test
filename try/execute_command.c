#include "shell.h"


int execute_command(char *command) {
    pid_t child_pid;
    int status;
    char **environ = NULL;

    child_pid = fork();
    if (child_pid == -1) {
        perror("Error");
        return EXIT_FAILURE;
    }

    if (child_pid == 0) {
        /* Child process */
       char *argv[] = {NULL, NULL};
      argv[0] = command;

       	/* Empty environment variable array*/

        if (execve(argv[0], argv, environ) == -1) {
            perror("Error");
            free(command);
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process*/
        wait(&status);
    }

    free(command);
    return EXIT_SUCCESS;
}
