#include "shell.h"

/************************   function 1  ************************************/
/**
 * hsh - This is the main shell loop
 * @info: This is the parameter & return info struct
 * @av: This is the argument vector from main()
 * Return: 0 [success] | 1 [error] | error code
 */

int hsh(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2)
    {
        clear_infor(info);
        if (collaborative(info))
            _putss("$ ");
        _eputchar(BUF_FLUSH);
        r = get_inputs(info);
        if (r != -1)
        {
            set_infor(info, av);
            builtin_ret = find_assembled(info);
            if (builtin_ret == -1)
                find_cmd(info);
        }
        else if (collaborative(info))
            _putchar('\n');
        free_infor(info, 0);
    }
    write_past(info);
    free_infor(info, 1);
    if (!collaborative(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return (builtin_ret);
}

/************************   function 2  ************************************/

/**
 * find_assembled - Function that finds a builtin command
 * @info: This is the parameter & return info struct
 * Return: -1 if builtin not found |
 *			0 if builtin executed successfully |
 *			1 if builtin found but not successful |
 *		   -2 if builtin signals exit()
 */

int find_assembled(info_t *info)
{
    int p, built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _myescape},
        {"env", _myenv},
        {"help", _myassist},
        {"history", _mypast},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}};

    for (p = 0; builtintbl[p].type; p++)
        if (_strcmp(info->argv[0], builtintbl[p].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[p].func(info);
            break;
        }
    return (built_in_ret);
}

/************************   function 3  ************************************/

/**
 * find_cmd - Function that finds a command in PATH
 * @info: This is the parameter & return info struct
 * Return: [nothing]
 */

void find_cmd(info_t *info)
{
    char *path = NULL;
    int p, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (p = 0, k = 0; info->arg[p]; p++)
        if (!is_separator(info->arg[p], " \t\n"))
            k++;
    if (!k)
        return;

    path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_cmd(info);
    }
    else
    {
        if ((collaborative(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
            fork_cmd(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_err(info, "not found\n");
        }
    }
}

/************************   function 4  ************************************/

/**
 * fork_cmd - Function that forks a an exec thread to run cmd
 * @info: This is the parameter & return info struct
 * Return: [nothing]
 */

void fork_cmd(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {

        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environment(info)) == -1)
        {
            free_infor(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_err(info, "Permission denied\n");
        }
    }
}
