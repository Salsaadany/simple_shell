#include "shell.h"
/**
 * hsh - the shell loop main
 * @n: info parameter that returns struct's data
 * @av: the argument vector from the main()
 *
 * Return: 0 if successful, 1 if either error occurred, or error code
 */
int hsh(info_t *n, char **av)
{
	ssize_t x = 0;
	int builtin_ret = 0;

	while (x != -1 && builtin_ret != -2)
	{
		clear_information(n);
		if (maati(n))
			st_inp("$ ");
		_eputchar(BUF_FLUSH);
		x = get_input_lines(n);
		if (x != -1)
		{
			set_information(n, av);
			builtin_ret = l_bn(n);
			if (builtin_ret == -1)
				l_exmd(n);
		}
		else if (maati(n))
			_putchar('\n');
		free_information(n, 0);
	}
	write_history(n);
	free_information(n, 1);
	if (!maati(n) && n->status)
		exit(n->status);
	if (builtin_ret == -2)
	{
		if (n->err_num == -1)
			exit(n->status);
		exit(n->err_num);
	}
	return (builtin_ret);
}

/**
 * l_bn - locates the built-in command
 * @n: info parameter that returns struct's data
 *
 * Return: -1 if not to be found,
 *			0 for successful execution,
 *			1 if found yet didn't succeed,
 *			-2 if signals exit()
 */
int l_bn(info_t *n)
{
	int x, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", myexit},
		{"env", myenv_maati},
		{"help", myhelp},
		{"history", myhistory_maati},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}};

	for (x = 0; builtintbl[x].type; x++)
		if (s_com(n->argv[0], builtintbl[x].type) == 0)
		{
			n->line_count++;
			built_in_ret = builtintbl[x].func(n);
			break;
		}
	return (built_in_ret);
}
/**
 * l_exmd - locates any command in given path
 * @n: info parameter that returns struct's data
 *
 * Return: void
 */
void l_exmd(info_t *n)
{
	char *pt = NULL;
	int x, y;

	n->path = n->argv[0];
	if (n->linecount_flag == 1)
	{
		n->line_count++;
		n->linecount_flag = 0;
	}
	for (x = 0, y = 0; n->arg[x]; x++)
		if (!d_islem(n->arg[x], " \t\n"))
			y++;
	if (!y)
		return;

	pt = l_pt(n, getenv_maati(n, "PATH="), n->argv[0]);
	if (pt)
	{
		n->path = pt;
		dev_xmd(n);
	}
	else
	{
		if ((maati(n) || getenv_maati(n, "PATH=") || n->argv[0][0] == '/') && ex_cd(n, n->argv[0]))
			dev_xmd(n);
		else if (*(n->arg) != '\n')
		{
			n->status = 127;
			print_error(n, "not found\n");
		}
	}
}
/**
 * dev_xmd - func's prps is forking exc thrd for running command
 * @n: info parameter that returns struct's data
 *
 * Return: void
 */
void dev_xmd(info_t *n)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(n->path, n->argv, get_environ_maati(n)) == -1)
		{
			free_information(n, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(n->status));
		if (WIFEXITED(n->status))
		{
			n->status = WEXITSTATUS(n->status);
			if (n->status == 126)
				print_error(n, "Permission denied\n");
		}
	}
}
