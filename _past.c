#include "shell.h"

/************   function 1 ***********/

/**
 * get_past_file - Fuction that gets the past file
 * @info: This is the parameter struct
 * Return: The allocated str containing history file
 */

char *get_past_file(info_t *info)
{
    char *buf, *dir;

    dir = _getenv(info, "HOME=");
    if (!dir)
        return (NULL);
    buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
    if (!buf)
        return (NULL);
    buf[0] = 0;
    _strcpy(buf, dir);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);
    return (buf);
}

/************   function 2 ***********/

/**
 * write_past - Function that creates a file | appends to an existing file
 * @info: This is the parameter struct
 * Return: 1 [success] | else -1
 */

int write_past(info_t *info)
{
    ssize_t fd;
    char *filename = get_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return (-1);
    for (node = info->history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }
    _putfd(BUF_FLUSH, fd);
    close(fd);
    return (1);
}

/************   function 3 ***********/

/**
 * read_past - Function that reads the past of a file
 * @info: This is the parameter struct
 * Return: past-count on [success] | 0 [otherwise]
 */

int read_past(info_t *info)
{
    int p, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = get_history_file(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return (0);
    if (!fstat(fd, &st))
        fsize = st.st_size;
    if (fsize < 2)
        return (0);
    buf = malloc(sizeof(char) * (fsize + 1));
    if (!buf)
        return (0);
    rdlen = read(fd, buf, fsize);
    buf[fsize] = 0;
    if (rdlen <= 0)
        return (free(buf), 0);
    close(fd);
    for (p = 0; p < fsize; p++)
        if (buf[p] == '\n')
        {
            buf[p] = 0;
            build_history_list(info, buf + last, linecount++);
            last = p + 1;
        }
    if (last != p)
        build_history_list(info, buf + last, linecount++);
    free(buf);
    info->histcount = linecount;
    while (info->histcount-- >= HIST_MAX)
        delete_node_at_index(&(info->history), 0);
    renumber_history(info);
    return (info->histcount);
}

/************   function 4 ***********/

/**
 * build_past_list - Function that adds entry to a history linked list
 * @info: This is the structure containing potential arguments
 * @buf: This is the buffer
 * @linecount: This is the history linecount, histcount
 * Return: 0 [always]
 */

int build_past_list(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;
    add_node_end(&node, buf, linecount);

    if (!info->history)
        info->history = node;
    return (0);
}

/************   function 5 ***********/

/**
 * renumber_past - Func that renumbers the history linked list after changes
 * @info: This is the structure containing potential arguments
 * Return: The new history count
 */
int renumber_past(info_t *info)
{
    list_t *node = info->history;
    int p = 0;

    while (node)
    {
        node->num = p++;
        node = node->next;
    }
    return (info->histcount = p);
}
