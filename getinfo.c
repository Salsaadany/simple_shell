#include "shell.h"

/**
 * clear_information - initializes info_t struct
 * @info: struct address
 */
void clear_information(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_information - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_information(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = sp_rep(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = st_dpl(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		al_rep(info);
		ve_rep(info);
	}
}

/**
 * free_information - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_information(info_t *info, int all)
{
	f_mp(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			x_lst(&(info->env));
		if (info->history)
			x_lst(&(info->history));
		if (info->alias)
			x_lst(&(info->alias));
		f_mp(info->environ);
			info->environ = NULL;
		f_brdm((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
