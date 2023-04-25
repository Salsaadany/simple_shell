#include "shell.h"

/**
 * get_environ_maati - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ_maati(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = l_str(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = stw_sherry(node->stng, var);
		if (p && *p == '=')
		{
			info->env_changed = dl_nd(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(s_lngth(var) + s_lngth(value) + 2);
	if (!buf)
		return (1);
	st_coo(buf, var);
	st_conc(buf, "=");
	st_conc(buf, value);
	node = info->env;
	while (node)
	{
		p = stw_sherry(node->stng, var);
		if (p && *p == '=')
		{
			free(node->stng);
			node->stng = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	a_nnd(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
