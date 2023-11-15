#include "shell.h"

/**
 * get_environment - Function returns the str array copy of our environ
 * @info: Containing potential args used to maintain const func prototype
 * Return: 0 [always]
 */

char **get_environment(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = ls_to_str(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Function that removes an environment var
 * @info: Containing potential args used to maintain const func prototype
 * @var: This is thethe str env var property
 * Return: 1 [delete] | 0 [otherwise]
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = start_hay(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = del_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenviroment - Func that initialize a new env var | modify an existing one
 * @info: Containing potential args used to maintain const func prototype
 * @var: This is the str env var property
 * @value: This is the string env var value
 * Return: 0 [always]
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = start_hay(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_nodes_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
