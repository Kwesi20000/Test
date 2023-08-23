#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void prompt_user(void);
char *read_input(void);
int execute_command(char *command);
void tokenize_input(char *line, char *args[], int *argc);
int execute_command_arg(char *args[]);

#endif /* SHELL_H */

