#include "shell.h"

/**
 * myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = erratoi_maati(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			eputs_maati(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = erratoi_maati(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		st_inp("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getenv_maati(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = getenv_maati(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (s_com(info->argv[1], "-") == 0)
	{
		if (!getenv_maati(info, "OLDPWD="))
		{
			st_inp(s);
			_putchar('\n');
			return (1);
		}
		st_inp(getenv_maati(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = getenv_maati(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		eputs_maati(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", getenv_maati(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	st_inp("help call works. Function not yet implemented \n");
	if (0)
		st_inp(*arg_array); /* temp att_unused workaround */
	return (0);
}
