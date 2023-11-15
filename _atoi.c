#include "shell.h"

/**
 * collaborative - Function returns true if the shell is collaborative
 * @info: This is the struct address
 * Return: 1 [collaborative] and 0 [otherwise]
 */

int collaborative(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_separator - Function that checks if the char is a separator
 * @a: This is the char to be checked
 * @separator: This is the separator str
 * Return: 1 [true] and 0 [false]
 */

int is_separator(char a, char *separator)
{
	while (*separator)
		if (*separator++ == a)
			return (1);
	return (0);
}

/**
 *alpha - Function that checks for alphabetic char
 *@a: This is the char to insert
 *Return: 1 if a is [alphabetic] and 0 [otherwise]
 */

int alpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - Function that converts a str to an int
 *@a: This is the str to be converted
 *Return: 0 if no num in the str and a converted num otherwise
 */

int _atoi(char *a)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  a[i] != '\0' && flag != 2; i++)
	{
		if (a[i] == '-')
			sign *= -1;

		if (a[i] >= '0' && a[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (a[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
