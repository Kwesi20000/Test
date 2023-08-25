#include "shell.h"

/**
 * _memorySet - Fills memory with a constant byte.
 * @ptr: Pointer to the memory area.
 * @byte: The byte to fill *ptr with.
 * @n: The number of bytes to be filled.
 * Return: A pointer to the memory area @ptr.
 */
char *_memorySet(char *ptr, char byte, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        ptr[i] = byte;
    return (ptr);
}

/**
 * freeStringArray - Frees a string array and its contents.
 * @strArr: The string array to free.
 */
void freeStringArray(char **strArr)
{
    char **temp = strArr;

    if (!strArr)
        return;
    while (*strArr)
        free(*strArr++);
    free(temp);
}

/**
 * _reallocateMemory - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @oldSize: Byte size of the previous block.
 * @newSize: Byte size of the new block.
 *
 * Return: Pointer to the old or new block.
 */
void *_reallocateMemory(void *ptr, unsigned int oldSize, unsigned int newSize)
{
    char *newPtr;

    if (!ptr)
        return (malloc(newSize));
    if (!newSize)
        return (free(ptr), NULL);
    if (newSize == oldSize)
        return (ptr);

    newPtr = malloc(newSize);
    if (!newPtr)
        return (NULL);

    oldSize = oldSize < newSize ? oldSize : newSize;
    while (oldSize--)
        newPtr[oldSize] = ((char *)ptr)[oldSize];
    free(ptr);
    return (newPtr);
}

