#include "shell.h"

/**
 * ls_len - Function determines len of linked list
 * @h: This is the ptr to the 1st node
 * Return: size of list
 */

size_t ls_len(const list_t *h)
{
    size_t p = 0;

    while (h)
    {
        h = h->next;
        p++;
    }
    return (p);
}

/**
 * ls_to_str - Func that returns an array of str of the list->str
 * @head: This is the ptr to the 1st node
 * Return: The array of str
 */

char **ls_to_str(list_t *head)
{
    list_t *node = head;
    size_t p = ls_len(head), q;
    char **strs;
    char *str;

    if (!head || !p)
        return (NULL);
    strs = malloc(sizeof(char *) * (p + 1));
    if (!strs)
        return (NULL);
    for (p = 0; node; node = node->next, p++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (q = 0; q < p; p++)
                free(strs[q]);
            free(strs);
            return (NULL);
        }

        str = _strcpy(str, node->str);
        strs[p] = str;
    }
    strs[p] = NULL;
    return (strs);
}

/**
 * print_ls - Func that prints all elements of list_t
 * @h: This is the ptr to the 1st node
 * Return: size of list
 */

size_t print_ls(const list_t *h)
{
    size_t p = 0;

    while (h)
    {
        _putss(convert_num(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _putss(h->str ? h->str : "(nil)");
        _putss("\n");
        h = h->next;
        p++;
    }
    return (p);
}

/**
 * node_starts - Func that returns the node whose str starts with prefix
 * @node: This is the ptr to the list head
 * @prefix: This is the str to match
 * @c: This is the next char after prefix to match
 * Return: match node or null
 */

list_t *node_starts(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = start_hay(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return (node);
        node = node->next;
    }
    return (NULL);
}

/**
 * get_node_index - Function that gets the index of a node
 * @head: This is the ptr to the list head
 * @node: This is the ptr to the node
 * Return: The index of the node or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
    size_t p = 0;

    while (head)
    {
        if (head == node)
            return (p);
        head = head->next;
        p++;
    }
    return (-1);
}
