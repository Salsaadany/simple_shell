#include "shell.h"

/**
 * xd - determines if a file is an executable command
 * @n: the info struct
 * @p: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int xd(info_t *n, char *p)
{
	struct stat fx;

	(void)n;
	if (!p || stat(p, &fx))
		return (0);

	if (fx.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * d_crt - func's prps is duplicating chars
 * @p_st: string's path
 * @bgn: index beginning
 * @trmn: index finalizing
 *
 * Return: new buff's pointer
 */
char *d_crt(char *p_st, int bgn, int trmn)
{
	static char buf[1024];
	int x = 0, y = 0;

	for (y = 0, x = bgn; x < trmn; x++)
		if (p_st[x] != ':')
			buf[y++] = p_st[x];
	buf[y] = 0;
	return (buf);
}

/**
 * l_pt - locates cmd in path add
 * @n: struct's information
 * @p_st: tstring's path
 * @kd: wannabe found cmd
 *
 * Return: cmd's path if found or NULL
 */
char *l_pt(info_t *n, char *p_st, char *kd)
{
	int x = 0, cr_p = 0;
	char *pt;

	if (!p_st)
		return (NULL);
	if ((s_lngth(kd) > 2) && stw_sherry(kd, "./"))
	{
		if (xd(n, kd))
			return (kd);
	}
	while (1)
	{
		if (!p_st[x] || p_st[x] == ':')
		{
			pt = d_crt(p_st, cr_p, x);
			if (!*pt)
				st_conc(pt, kd);
			else
			{
				st_conc(pt, "/");
				st_conc(pt, kd);
			}
			if (xd(n, pt))
				return (pt);
			if (!p_st[x])
				break;
			cr_p = x;
		}
		x++;
	}
	return (NULL);
}
