#include "shell.h"

/**
 * clear_infor - Functionn that initializes info_t struct
 * @info: This is the struct address
 */

void clear_infor(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_infor - Function that initializes info_t struct
 * @info: This is the struct address
 * @av: This is the arg vector
 */

void set_infor(info_t *info, char **av)
{
	int p = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (p = 0; info->argv && info->argv[p]; p++)
			;
		info->argc = p;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_infor - Function that frees info_t struct fields
 * @info: This is the struct address
 * @all: This is true if freeing all fields
 */

void free_infor(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
