#include "shell.h"

/*************  function 1  *******************/

/**
 **_memoryset - Function that fills memory with a const byte
 *@s: This is the ptr to the memory area
 *@b: This is the byte to fill *s with
 *@n: This is the amount of bytes to be filled
 *Return: [s] a ptr to the memory area s
 */

char *_memoryset(char *s, char b, unsigned int n)
{
    unsigned int p;

    for (p = 0; p < n; p++)
        s[p] = b;
    return (s);
}

/*************  function 2  *******************/

/**
 * ffree - Function that frees a strof strings
 * @pp: These are string of strings
 */

void ffree(char **pp)
{
    char **a = pp;

    if (!pp)
        return;
    while (*pp)
        free(*pp++);
    free(a);
}

/*************  function 3  *******************/

/**
 * realloc - Function reallocates a block of memory
 * @ptr: This is the ptr to previous malloc'ated block
 * @old_size: This is the byte size of previous block
 * @new_size: This is the byte size of new block
 * Return: ptr to da ol'block nameen.
 */

void *realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    if (!ptr)
        return (malloc(new_size));
    if (!new_size)
        return (free(ptr), NULL);
    if (new_size == old_size)
        return (ptr);

    p = malloc(new_size);
    if (!p)
        return (NULL);

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        p[old_size] = ((char *)ptr)[old_size];
    free(ptr);
    return (p);
}
