#include "shell.h"

/************   function 1 *******************/

/**
 * _strlen - Function that returns the len of a str
 * @s: This is the str whose len to be checked
 * Return: int len of str
 */

int _strlen(char *s)
{
    int i = 0;

    if (!s)
        return (0);

    while (*s++)
        i++;
    return (i);
}

/************   function 2 *******************/

/**
 * _strcmp - Func that performs lexicographic comparison of two strings
 * @s1: This is the 1st str
 * @s2: This is the 2nd str
 * Return: [-] if s1 < s2 | [=] if s1 > s2 | [0] if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return (0);
    else
        return (*s1 < *s2 ? -1 : 1);
}

/************   function 3 *******************/

/**
 * start_hay - Func that checks if needle starts with haystack
 * @haystack: This is the str to search
 * @needle: This is the substring to find
 * Return: The address of next char of haystack or NULL
 */

char *start_hay(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return (NULL);
    return ((char *)haystack);
}

/************   function 4 *******************/

/**
 * _strcat - Function that concatenates two strings
 * @dest: This is the destination buffer
 * @src: This is the source buffer
 * Return: The ptr to destination buff
 */

char *_strcat(char *dest, char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return (ret);
}
