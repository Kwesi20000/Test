#include "shell.h"

void tokenize_input(char *line, char *args[], int *argc) {
    char *token;
    int i = 0;

    token = strtok(line, " ");
    while (token != NULL && i < 63) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    *argc = i;
}
