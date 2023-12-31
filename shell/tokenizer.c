#include "shell.h"

/**
 * splitString - splits a string into words. Repeated delimiters are ignored.
 * @str: the input string
 * @delimiter: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splitString(char *str, char *delimiter)
{
    int i, j, k, m, numWords = 0;
    char **strings;

    if (str == NULL || str[0] == 0)
        return NULL;
    
    if (!delimiter)
        delimiter = " ";

    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isDelimiter(str[i], delimiter) && (isDelimiter(str[i + 1], delimiter) || !str[i + 1]))
            numWords++;
    }

    if (numWords == 0)
        return NULL;
    
    strings = malloc((1 + numWords) * sizeof(char *));

    if (!strings)
        return NULL;
    
    for (i = 0, j = 0; j < numWords; j++)
    {
        while (isDelimiter(str[i], delimiter))
            i++;
        
        k = 0;
        
        while (!isDelimiter(str[i + k], delimiter) && str[i + k])
            k++;
        
        strings[j] = malloc((k + 1) * sizeof(char));

        if (!strings[j])
        {
            for (k = 0; k < j; k++)
                free(strings[k]);
            
            free(strings);
            return NULL;
        }

        for (m = 0; m < k; m++)
            strings[j][m] = str[i++];
        
        strings[j][m] = 0;
    }
    
    strings[j] = NULL;
    return strings;
}

/**
 * splitString2 - splits a string into words using a delimiter
 * @str: the input string
 * @delimiter: the delimiter character
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splitString2(char *str, char delimiter)
{
    int i, j, k, m, numWords = 0;
    char **strings;

    if (str == NULL || str[0] == 0)
        return NULL;
    
    for (i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] != delimiter && str[i + 1] == delimiter) ||
            (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
            numWords++;
    }

    if (numWords == 0)
        return NULL;
    
    strings = malloc((1 + numWords) * sizeof(char *));

    if (!strings)
        return NULL;
    
    for (i = 0, j = 0; j < numWords; j++)
    {
        while (str[i] == delimiter && str[i] != delimiter)
            i++;
        
        k = 0;
        
        while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
            k++;
        
        strings[j] = malloc((k + 1) * sizeof(char));

        if (!strings[j])
        {
            for (k = 0; k < j; k++)
                free(strings[k]);
            
            free(strings);
            return NULL;
        }

        for (m = 0; m < k; m++)
            strings[j][m] = str[i++];
        
        strings[j][m] = 0;
    }
    
    strings[j] = NULL;
    return strings;
}

