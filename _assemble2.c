#include "shell.h"

/**
 * _mypast - Func displays the past list 1 command by line, preceded with line num starting at 0
 * @info: Structure containing potential arg used to maintain const func prototype
 * Return: 0 [always]
 */

int _mypast(info_t *info)
{
	print_ls(info->history);
	return (0);
}

/**
 * unset_alias - Function that sets alias to a str
 * @info: This is the parameter struct
 * @str: This is the str alias
 * Return: 0 [success] and 1 [error]
 */

int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = del_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Function that sets alias to a str
 * @info: This is the parameter struct
 * @str: This is the str alias
 * Return: 0 [success] and 1 [error]
 */

int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_nodes_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Function that prints an alias str
 * @node: This is the alias node
 * Return: 0 [success] and 1 [error]
 */

int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_putss(p + 1);
		_putss("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Function that mimics the alias assemble
 * @info: Structure containing potential arg used to maintain const func prototype
 * Return: 0 [always]
 */

int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts(info->alias, info->argv[i], '='));
	}

	return (0);
}
