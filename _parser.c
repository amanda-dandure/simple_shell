#include "shell.h"

/*******************************    function 1  ************************************/

/**
 * is_cmd - Func that determines if a file is an executable command
 * @info: This is the info struct
 * @path: This is the path to the file
 * Return: 1 if true, 0 otherwise
 */

int is_cmd(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return (0);

    if (st.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}

/*******************************    function 2  ************************************/

/**
 * dup_char - Function that duplicates char
 * @pathstr: This is the PATH str
 * @start: This is the starting index
 * @stop: This is the stopping index
 * Return: pointer to new buffer
 */

char *dup_char(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int p = 0, k = 0;

    for (k = 0, p = start; p < stop; p++)
        if (pathstr[p] != ':')
            buf[k++] = pathstr[p];
    buf[k] = 0;
    return (buf);
}

/*******************************    function 3  ************************************/

/**
 * find_path - Func that finds this cmd in the PATH str
 * @info: This is the the info struct
 * @pathstr: This is the PATH str
 * @cmd: This is the cmd to find
 * Return: The full path of cmd if found or NULL
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int p = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return (NULL);
    if ((_strlen(cmd) > 2) && start_hay(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return (cmd);
    }
    while (1)
    {
        if (!pathstr[p] || pathstr[p] == ':')
        {
            path = dup_char(pathstr, curr_pos, p);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (is_cmd(info, path))
                return (path);
            if (!pathstr[p])
                break;
            curr_pos = p;
        }
        p++;
    }
    return (NULL);
}
