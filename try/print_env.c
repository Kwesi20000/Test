#include "shell.h"

char **environ;
void print_environment(void) {
    for (char **env = environ; *env != NULL; env++)
        printf("%s\n", *env);
}
