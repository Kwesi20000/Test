#include "shell.h"

/**
 * copyString - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *copyString(char *destination, char *source)
{
    int index = 0;

    if (destination == source || source == 0)
        return destination;
    
    while (source[index])
    {
        destination[index] = source[index];
        index++;
    }
    
    destination[index] = 0;
    return destination;
}

/**
 * stringDuplicate - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *stringDuplicate(const char *str)
{
    int length = 0;
    char *result;

    if (str == NULL)
        return NULL;
    
    while (*str++)
        length++;
    
    result = malloc(sizeof(char) * (length + 1));
    
    if (!result)
        return NULL;
    
    for (length++; length--;)
        result[length] = *--str;
    
    return result;
}

/**
 * printString - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void printString(char *str)
{
    int index = 0;

    if (!str)
        return;

    while (str[index] != '\0')
    {
        printCharacter(str[index]);
        index++;
    }
}

/**
 * printCharacter - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int printCharacter(char c)
{
    static int index;
    static char buffer[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
    {
        write(1, buffer, index);
        index = 0;
    }
    
    if (c != BUFFER_FLUSH)
        buffer[index++] = c;
    
    return 1;
}

