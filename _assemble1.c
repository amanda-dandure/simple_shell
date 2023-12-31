#include "shell.h"

/**
 * _myescape - Function that escapes the shell
 * @info: Has potential arg used const func prototype
 * Return: Escapes with a given escape status
 */

int _myescape(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _erroratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_err(info, "illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erroratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Function changes the current directory of the process
 * @info: Containing potential arg used to maintain const func prototype
 * Return: 0 [always]
 */

int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_putss("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_putss(s);
			_putchar('\n');
			return (1);
		}
		_putss(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myassist - Function that changes the current directory of the process
 * @info: Has potential arg used const func prototype
 * Return: 0 [always]
 */

int _myassist(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_putss("assist call works. Function not yet implemented \n");
	if (0)
		_putss(*arg_array);
	return (0);
}
