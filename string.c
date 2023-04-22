#include "shell.h"

/**
 * s_lngth - returns str's length
 * @st: wannabe checked string
 *
 * Return: string's length integer
 */
int s_lngth(char *st)
{
	int x = 0;

	if (!st)
		return (0);

	while (*st++)
		x++;
	return (x);
}

/**
 * s_com - performs lexicogarphic comparison between 2 sts.
 * @st1: 1st string
 * @st2: 2nd strnng
 *
 * Return: -ve s1<s2, +ve s1>s2, 0 st1equals to st2
 */
int s_com(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * stw_sherry - searching for a rock in a mountain
 * @mountain: the hound string
 * @rock: the sought after substring
 *
 * Return: address of next char of mountain, otherwise  NULL
 */
char *stw_sherry(const char *mountain, const char *rock)
{
	while (*rock)
		if (*rock++ != *mountain++)
			return (NULL);
	return ((char *)mountain);
}

/**
 * st_conc - 2 strings concatentaion
 * @terminal: buffer's destination
 * @origin: source buffer
 *
 * Return: pointer to destination buffer
 */
char *st_conc(char *terminal, char *origin)
{
	char *fix = terminal;

	while (*terminal)
		terminal++;
	while (*origin)
		*terminal++ = *origin++;
	*terminal = *origin;
	return (fix);
}
