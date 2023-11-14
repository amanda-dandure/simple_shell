#include "shell.h"

/**
 * _myenv - Function that prints the current environment
 * @info: Containing potential arg used to maintain const func prototype
 * Return: 0 [always]
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Function that gets the value of an environment variable
 * @info: Containing potential arg used to maintain const func prototype
 * @name: This is the environment variable name
 * Return: The value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Func that initialize a new env var or update an existing one
 * @info: Containing potential arg used to maintain const func prototype
 * Return: 0 [always]
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Containing potential arg used to maintain const func prototype
 * Return: 0 [always]
 */

int _myunsetenv(info_t *info)
{
	int b;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (b = 1; b <= info->argc; b++)
		_unsetenv(info, info->argv[b]);

	return (0);
}

/**
 * pop_env_list - Function that populates enviroment linked list
 * @info: Containing potential arg used to maintain const func prototype
 * Return:0 [always]
 */

int pop_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t b;

	for (b = 0; environ[b]; b++)
		add_node_end(&node, environ[b], 0);
	info->env = node;
	return (0);
}
