#include "shell.h"

/**
 * ch_del - test if current char in buffer is a chain delimeter
 * @n: struct's parameter
 * @buf: character's buffer
 * @pos: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int ch_del(info_t *n, char *buf, size_t *pos)
{
	size_t y = *pos;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[y] = 0;
		y++;
		n->cmd_buf_type = CMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		n->cmd_buf_type = CMD_AND;
	}
	else if (buf[y] == ';') /* found end of this command */
	{
		buf[y] = 0; /* replace semicolon with null */
		n->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = y;
	return (1);
}

/**
 * ch_checker - chain checker
 * @n: struct's parameter
 * @buf: ch buffer
 * @pos: current position's add in buf
 * @x: starting position in buf
 * @lngth: buffer's length
 *
 * Return: Void
 */
void ch_checker(info_t *n, char *buf, size_t *pos, size_t x, size_t lngth)
{
	size_t y = *pos;

	if (n->cmd_buf_type == CMD_AND)
	{
		if (n->status)
		{
			buf[x] = 0;
			y = lngth;
		}
	}
	if (n->cmd_buf_type == CMD_OR)
	{
		if (!n->status)
		{
			buf[x] = 0;
			y = lngth;
		}
	}

	*pos = y;
}

/**
 * al_rep - tknzd string alias replacement
 * @n: struct's parameter
 *
 * Return: 1 if done, otherwise 0
 */
int al_rep(info_t *n)
{
	int x;
	list_t *node;
	char *pos;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(n->alias, n->argv[0], '=');
		if (!node)
			return (0);
		free(n->argv[0]);
		pos = _strchr(node->str, '=');
		if (!pos)
			return (0);
		pos = _strdup(pos + 1);
		if (!pos)
			return (0);
		n->argv[0] = pos;
	}
	return (1);
}

/**
 * ve_rep - tokenized string v replacement
 * @n: struct's parameter
 *
 * Return: 1 if done, otherwise 0
 */
int ve_rep(info_t *n)
{
	int x = 0;
	list_t *node;

	for (x = 0; n->argv[x]; x++)
	{
		if (n->argv[x][0] != '$' || !n->argv[x][1])
			continue;

		if (!s_com(n->argv[x], "$?"))
		{
			st_rpl(&(n->argv[x]),
				   st_dpl(convert_number(n->status, 10, 0)));
			continue;
		}
		if (!_strcmp(n->argv[x], "$$"))
		{
			st_rpl(&(n->argv[x]),
				   st_dpl(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = sw_nd(n->env, &info->argv[x][1], '=');
		if (node)
		{
			st_rpl(&(n->argv[x]),
				   st_dpl(_strchr(node->str, '=') + 1));
			continue;
		}
		st_rpl(&n->argv[x], st_dpl(""));
	}
	return (0);
}

/**
 * st_rpl - string replacing
 * @alt: alt string's address
 * @neu: neue string
 *
 * Return: 1 if done, 0 otherwise
 */
int st_rpl(char **alt, char *neu)
{
	free(*alt);
	*alt = neu;
	return (1);
}
