#include "shell.h"

/**
 *_puts - Function that prints an input str
 * @str: This is the str to be printed
 * Return: void
 */

void _puts(char *str)
{
	int p = 0;

	if (!str)
		return;
	while (str[p] != '\0')
	{
		_eputchar(str[p]);
		p++;
	}
}

/**
 * _eputchar - Function writes the char c to stderr
 * @c: This is the char to be printed
 * Return: 1 [success] -1 [error]
 */

int _eputchar(char c)
{
	static int p;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || p >= WRITE_BUF_SIZE)
	{
		write(2, buf, p);
		p = 0;
	}
	if (c != BUF_FLUSH)
		buf[p++] = c;
	return (1);
}

/**
 * _putfd - Function that writes the char c to given fd
 * @c: This is the char to be printed
 * @fd: Thiss is the file descriptor to write to
 * Return: 1 [success] -1 [error]
 */

int _putfd(char c, int fd)
{
	static int p;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || p >= WRITE_BUF_SIZE)
	{
		write(fd, buf, p);
		p = 0;
	}
	if (c != BUF_FLUSH)
		buf[p++] = c;
	return (1);
}

/**
 *_putsfd - Function that prints an input str
 * @str: This is the str to be printed
 * @fd: This is the file descriptor to write to
 * Return: The number of chars put
 */

int _putsfd(char *str, int fd)
{
	int p = 0;

	if (!str)
		return (0);
	while (*str)
	{
		p += _putfd(*str++, fd);
	}
	return (p);
}
