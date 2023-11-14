#include "shell.h"

/**
 **_strncpy - Function that copies a str
 *@dest: This is the destination str to be copied to
 *@src: This is the source string
 *@n: This is the amount of char to be copied
 *Return: concatenated str
 */

char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **_strncat - Function that concatenates two str
 *@dest: This is the 1st str
 *@src: This is the 2nd str
 *@n: This is the amount of bytes to be maximally used
 *Return: concatenated str
 */

char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - Function that locates a char in a str
 *@s: This is the str to be parsed
 *@c: This is the char to look for
 *Return: [s] a ptr to the memory area s
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
