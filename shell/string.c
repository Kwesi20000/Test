#include "shell.h"

/**
 * strLength - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of the string
 */
int strLength(char *str)
{
    int length = 0;

    if (!str)
        return (0);

    while (*str++)
        length++;
    return (length);
}

/**
 * strCompare - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int strCompare(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);
        str1++;
        str2++;
    }
    if (*str1 == *str2)
        return (0);
    else
        return (*str1 < *str2 ? -1 : 1);
}

/**
 * strStartsWith - checks if the haystack starts with the needle
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next character of haystack or NULL
 */
char *strStartsWith(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return (NULL);
    return ((char *)haystack);
}

/**
 * strConcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *strConcat(char *dest, char *src)
{
    char *result = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return (result);
}

