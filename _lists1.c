#include "shell.h"

/***************************    function 1 *************************************/

/**
 * add_nodes - Function thats adds a node to the start of the list
 * @head: This is the address of ptr to head node
 * @str: This is the str field of node
 * @num: This is the node index used by past/history
 * Return: The size of list
 */

list_t *add_nodes(list_t **head, const char *str, int num)
{
    list_t *new_head;

    if (!head)
        return (NULL);
    new_head = malloc(sizeof(list_t));
    if (!new_head)
        return (NULL);
    _memset((void *)new_head, 0, sizeof(list_t));
    new_head->num = num;
    if (str)
    {
        new_head->str = _strdup(str);
        if (!new_head->str)
        {
            free(new_head);
            return (NULL);
        }
    }
    new_head->next = *head;
    *head = new_head;
    return (new_head);
}

/***************************    function 2 *************************************/

/**
 * add_nodes_end - Function thats adds a node to the end of the list
 * @head: This is the address of ptr to head node
 * @str: This is the str field of node
 * @num: This is the node index used by past/history
 * Return: The size of list
 */

list_t *add_nodes_end(list_t **head, const char *str, int num)
{
    list_t *new_node, *node;

    if (!head)
        return (NULL);

    node = *head;
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);
    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;
    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;
    return (new_node);
}

/***************************    function 3 *************************************/
/**
 * print_ls_str - Func prints only the str element of list_t
 * @h: This is the ptr to 1st node
 * Return: The size of list
 */
size_t print_ls_str(const list_t *h)
{
    size_t p = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        p++;
    }
    return (p);
}

/***************************    function 4 *************************************/

/**
 * del_node_at_index - Func that del a node at given index
 * @head: This is the address of ptr to the 1st node
 * @index: This is the index of node to delete
 * Return: 1 [success] | 0 [failure]
 */

int del_node_at_index(list_t **head, unsigned int index)
{
    list_t *node, *prev_node;
    unsigned int p = 0;

    if (!head || !*head)
        return (0);

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return (1);
    }
    node = *head;
    while (node)
    {
        if (p == index)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return (1);
        }
        p++;
        prev_node = node;
        node = node->next;
    }
    return (0);
}

/***************************    function 5 *************************************/

/**
 * free_ls - Function that frees all nodes of a list
 * @head_ptr: This is the address of ptr to head node
 * Return: [nothing]
 */

void free_ls(list_t **head_ptr)
{
    list_t *node, *next_node, *head;

    if (!head_ptr || !*head_ptr)
        return;
    head = *head_ptr;
    node = head;
    while (node)
    {
        next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }
    *head_ptr = NULL;
}
