#include "shell.h"

/**
 * get_history_file - Get the path to the history file.
 * @info: Pointer to the info_t struct.
 *
 * Return: Allocated string containing the history file path.
 */
char *get_history_file(info_t *info)
{
    char *home_dir = _getenv(info, "HOME=");
    if (!home_dir)
        return NULL;

    char *history_path = malloc(strlen(home_dir) + strlen(HIST_FILE) + 2);
    if (!history_path)
    {
        free(home_dir);
        return NULL;
    }

    strcpy(history_path, home_dir);
    strcat(history_path, "/");
    strcat(history_path, HIST_FILE);
    
    free(home_dir);
    return history_path;
}

/**
 * write_history - Write command history to a file.
 * @info: Pointer to the info_t struct.
 *
 * Return: 1 on success, else -1.
 */
int write_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return -1;

    FILE *history_file = fopen(filename, "w");
    free(filename);

    if (!history_file)
        return -1;

    list_t *node = info->history;
    while (node)
    {
        fprintf(history_file, "%s\n", node->str);
        node = node->next;
    }

    fclose(history_file);
    return 1;
}

/**
 * read_history - Read command history from a file.
 * @info: Pointer to the info_t struct.
 *
 * Return: Number of history entries read on success, 0 otherwise.
 */
int read_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return 0;

    FILE *history_file = fopen(filename, "r");
    free(filename);

    if (!history_file)
        return 0;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int linecount = 0;
    while ((read = getline(&line, &len, history_file)) != -1)
    {
        linecount++;
        if (line[read - 1] == '\n')
            line[read - 1] = '\0'; // Remove the trailing newline
        build_history_list(info, line, linecount - 1);
    }

    free(line);
    fclose(history_file);

    while (info->histcount >= HIST_MAX)
        delete_node_at_index(&(info->history), 0);

    renumber_history(info);
    return info->histcount;
}

/**
 * build_history_list - Add an entry to the command history linked list.
 * @info: Pointer to the info_t struct.
 * @buf: Buffer containing the command.
 * @linecount: The history linecount.
 *
 * Return: 0 on success.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    add_node_end(&node, strdup(buf), linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumber_history - Renumber the history linked list after changes.
 * @info: Pointer to the info_t struct.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return (info->histcount = i);
}

