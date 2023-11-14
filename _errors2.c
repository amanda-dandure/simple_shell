#include "shell.h"

/**
 * _erroratoi - Function that converts a str to an int
 * @s: This is the str to be converted
 * Return: 0 [no num in str] -1 [error]
 */

int _erroratoi(char *s)
{
	int p = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (p = 0;  s[p] != '\0'; p++)
	{
		if (s[p] >= '0' && s[p] <= '9')
		{
			result *= 10;
			result += (s[p] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - Function that prints an error msg
 * @info: This is the parameter and  return infomation struct
 * @estr: This is the str containing specified err type
 * Return: 0 [no num in str] -1 [error]
 */

void print_err(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Function that prints a decimal [int] number [base 10]
 * @input: This is the input
 * @fd: This is the file descriptor to write to
 * Return: num of chars printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_num - Converter function, a clone of atoi
 * @num: This is the num
 * @base: This is the base
 * @flags: These are the argument flags
 * Return: str
 */

char *convert_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rem_comments - Function that replaces 1st instance of '#' with '\0'
 * @buf: This is the address of the str to modify
 * Return: 0 [always]
 */

void rem_comments(char *buf)
{
	int p;

	for (p = 0; buf[p] != '\0'; p++)
		if (buf[p] == '#' && (!p || buf[p - 1] == ' '))
		{
			buf[p] = '\0';
			break;
		}
}
