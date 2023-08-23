#include "shell.h"


char *get_command_path(const char *command) {
    char *path = getenv("PATH");
    char *dir, *path_copy, *full_path;

    if (path == NULL)
        return NULL;

    path_copy = strdup(path);
    if (path_copy == NULL)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir != NULL) {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (full_path == NULL)
            return NULL;

        sprintf(full_path, "%s/%s", dir, command);

        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
