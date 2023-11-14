#include "shell.h"

/****************************** function 1 ****************************************/

/**
 * is_chain - Func that test if current char in buff is a chain delimeter
 * @info: This is the parameter struct
 * @buf: This is the char buff
 * @p: This is the address of current position in buf
 * Return: 1 [chain delimeter] | 0 [otherwise]
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
    size_t b = *p;

    if (buf[b] == '|' && buf[b + 1] == '|')
    {
        buf[b] = 0;
        b++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buf[b] == '&' && buf[b + 1] == '&')
    {
        buf[b] = 0;
        b++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buf[b] == ';')
    {
        buf[b] = 0;
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
        return (0);
    *p = b;
    return (1);
}

/****************************** function 2 ****************************************/

/**
 * check_chains - Func checks we should continue chaining based on last status
 * @info: This is the parameter struct
 * @buf: This is the char buff
 * @p: This is the address of current position in buf
 * @i: This is starting position in buf
 * @len: This is the len of buf
 * Return: [nothing]
 */

void check_chains(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t b = *p;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            b = len;
        }
    }
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            b = len;
        }
    }

    *p = b;
}

/****************************** function 3 ****************************************/

/**
 * rep_alias - Function that replaces an aliases in the token str
 * @info: This is the parameter struct
 * Return: 1 [replaced] |  0 [otherwise]
 */

int rep_alias(info_t *info)
{
    int b;
    list_t *node;
    char *p;

    for (b = 0; b < 10; b++)
    {
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return (0);
        free(info->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return (0);
        p = _strdup(p + 1);
        if (!p)
            return (0);
        info->argv[0] = p;
    }
    return (1);
}

/****************************** function 4 ****************************************/

/**
 * rep_var - Function that replaces var in the token str
 * @info: This is the parameter struct
 * Return: 1 [replaced] | 0 [otherwise]
 */

int rep_var(info_t *info)
{
    int b = 0;
    list_t *node;

    for (b = 0; info->argv[b]; b++)
    {
        if (info->argv[b][0] != '$' || !info->argv[b][1])
            continue;

        if (!_strcmp(info->argv[b], "$?"))
        {
            replace_string(&(info->argv[b]),
                           _strdup(convert_number(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[b], "$$"))
        {
            replace_string(&(info->argv[b]),
                           _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = node_starts_with(info->env, &info->argv[b][1], '=');
        if (node)
        {
            replace_string(&(info->argv[b]),
                           _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replace_string(&info->argv[b], _strdup(""));
    }
    return (0);
}

/****************************** function 5 ****************************************/

/**
 * rep_str - Function that replaces a str
 * @old: This is the address of old str
 * @new: This is the new str
 * Return: 1 [replaced] | 0 [otherwise]
 */

int rep_str(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}
