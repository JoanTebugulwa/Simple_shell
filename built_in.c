#include "shell.h"

/**
 * exit_shell - this exits the shell
 *
 * @info: contains potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: exits with a given exit status
 * (0) if info->args[0] != "exit"
 */

int exit_shell(info_t *info)
{
	int exit_status;

	if (info->args[1])
	{
		exit_status = str_to_int(info->args[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_errputs(info->args[1]);
			_errputchar('\n');
			return (1);
		}
		info->err_num = str_to_int(info->args[1]);
		return (-2);
	}

	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - this changes the current directory of the process
 *
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */

int change_directory(info_t *info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->args[1])
	{
		new_dir = _getenv(info, "HOME=");
		if (!new_dir)
			chdir_ret =
				chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
		else
			chdir_ret = chdir(new_dir);
	}
	else if (_strcmp(info->args[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
	}
	else
		chdir_ret = chdir(info->args[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_errputs(info->args[1]), _errputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * show_help - this displays help information
 *
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */

int show_help(info_t *info)
{
	char **arg_array;

	arg_array = info->args;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
