#include "shell.h"

/**
 * **sp_rep - string splitting. repettition is ignored (sherry)
 * @st: the input string (i, j, k, m)
 * @dlm: the delimeter string
 * Return: a pointer to an array of strings, otherwise NULL if not
 */

char **sp_rep(char *st, char *dlm)
{
	int w, x, y, z, count = 0;
	char **rng;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!dlm)
		dlm = " ";
	for (w = 0; st[w] != '\0'; w++)
		if (!d_islem(st[w], dlm) && (d_islem(st[w + 1], dlm) || !st[w + 1]))
			count++;

	if (count == 0)
		return (NULL);
	s = malloc((1 + count) * sizeof(char *));
	if (!rng)
		return (NULL);
	for (w = 0, x = 0; x < count; x++)
	{
		while (d_islem(st[w], dlm))
			w++;
		y = 0;
		while (!d_islem(st[w + y], d) && st[w + y])
			y++;
		rng[x] = malloc((y + 1) * sizeof(char));
		if (!rng[x])
		{
			for (y = 0; y < x; y++)
				free(rng[y]);
			free(rng);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			s[x][z] = str[w++];
		s[x][z] = 0;
	}
	rng[x] = NULL;
	return (rng);
}

/**
 * **sp_litter - string splitting
 * @st: Inp string
 * @dlm: delimeter
 * Return: a pointer to an array of strings, NULL if not
 */
char **sp_litter(char *st, char dlm)
{
	int w, x, y, z, count = 0;
	char **rng;

	if (st == NULL || st[0] == 0)
		return (NULL);
	for (w = 0; st[w] != '\0'; w++)
		if ((st[w] != dlm && st[w + 1] == dlm) ||
			(st[w] != dlm && !st[w + 1]) || st[w + 1] == dlm)
			count++;
	if (count == 0)
		return (NULL);
	rng = malloc((1 + count) * sizeof(char *));
	if (!rng)
		return (NULL);
	for (w = 0, x = 0; x < count; x++)
	{
		while (st[w] == dlm && st[w] != dlm)
			w++;
		y = 0;
		while (st[w + y] != dlm && st[w + y] && st[w + y] != dlm)
			y++;
		rng[x] = malloc((y + 1) * sizeof(char));
		if (!rng[x])
		{
			for (y = 0; y < x; y++)
				free(rng[y]);
			free(rng);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			rng[x][z] = st[w++];
		rng[x][z] = 0;
	}
	rng[x] = NULL;
	return (rng);
}
