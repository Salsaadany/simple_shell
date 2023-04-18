#include "shell.h"

/**
 * ex_cd - determines if a file is an executable command
 * @n: the info struct
 * @p: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int ex_cd(info_t *n, char *p)
{
	struct stat fx;

	(void)n;
	if (!p || stat(p, &fx))
		return (0);

	if (st.st_mode & S_IFREG)
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

	for (y = 0, x = bgn; x < stop; x++)
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
	if ((_strlen(cmd) > 2) && starts_with(kd, "./"))
	{
		if (ex_cd(info, kd))
			return (kd);
	}
	while (1)
	{
		if (!p_st[x] || p_st[x] == ':')
		{
			pt = d_crt(p_st, cr_p, x);
			if (!*pt)
				_strcat(pt, cmd);
			else
			{
				_strcat(pt, "/");
				_strcat(pt, kd);
			}
			if (ex_cd(n, pt))
				return (pt);
			if (!p_st[x])
				break;
			cr_p = x;
		}
		x++;
	}
	return (NULL);
}
