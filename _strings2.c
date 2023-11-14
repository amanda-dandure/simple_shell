#include "shell.h"

/**************************  function 1 *********************************************/

/**
 * _strcpy - Function that copies a str
 * @dest: This is the destination
 * @src: This is the source
 * Return: ptr to destination
 */

char *_strcpy(char *dest, char *src)
{
    int p = 0;

    if (dest == src || src == 0)
        return (dest);
    while (src[p])
    {
        dest[p] = src[p];
        p++;
    }
    dest[p] = 0;
    return (dest);
}

/**************************  function 1 *********************************************/

/**
 * _strdup - Function that duplicates a str
 * @str: This is the str to duplicate
 * Return: ptr to the duplicated str
 */

char *_strdup(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return (NULL);
    while (*str++)
        length++;
    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return (NULL);
    for (length++; length--;)
        ret[length] = *--str;
    return (ret);
}

/**************************  function 2 *********************************************/

/**
 * _puts - Function prints an input str
 * @str: This is the str to be printed
 * Return: void
 */

void _puts(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

/**************************  function 4 *********************************************/

/**
 * _putchar - Function that writes the char c to stdout
 * @c: The character to print
 * Return: 1 [success] | -1 [on error]
 */

int _putchar(char c)
{
    static int p;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || p >= WRITE_BUF_SIZE)
    {
        write(1, buf, p);
        p = 0;
    }
    if (c != BUF_FLUSH)
        buf[p++] = c;
    return (1);
}
