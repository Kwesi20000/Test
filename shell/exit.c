#include "shell.h"

/**
 * string_copy - Copies a string up to a specified number of characters.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Return: The concatenated string.
 */
char *string_copy(char *dest, char *src, int n)
{
    int i, j;
    char *result = dest;

    i = 0;
    while (src[i] != '\0' && i < n - 1)
    {
        dest[i] = src[i];
        i++;
    }
    if (i < n)
    {
        j = i;
        while (j < n)
        {
            dest[j] = '\0';
            j++;
        }
    }
    return result;
}

/**
 * string_concatenate - Concatenates two strings up to a specified number of characters.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used.
 *
 * Return: The concatenated string.
 */
char *string_concatenate(char *dest, char *src, int n)
{
    int i, j;
    char *result = dest;

    i = 0;
    j = 0;
    while (dest[i] != '\0')
        i++;
    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    if (j < n)
        dest[i] = '\0';
    return result;
}

/**
 * find_character - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area in s containing the character, or NULL if not found.
 */
char *find_character(char *s, char c)
{
    do {
        if (*s == c)
            return s;
    } while (*s++ != '\0');

    return NULL;
}

