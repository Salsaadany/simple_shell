#include "shell.h"

/**
 **st_m - fills memory with a constant byte
 *@tr: memory space pointer
 *@z: the byte to fill *s with
 *@y: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *st_m(char *tr, char z, unsigned int y)
{
	unsigned int x;

	for (x = 0; x < y; x++)
		tr[x] = z;
	return (tr);
}

/**
 * f_mp - func's prps freeing master pointer
 * @mpn: strings' string (master pointer)
 */
void f_mp(char **mpn)
{
	char **x = mpn;

	if (!mpn)
		return;
	while (*mpn)
		free(*mpn++);
	free(x);
}

/**
 * _realloc - reallocates a whole memory's block
 * @pn: previous malloc'd block's pointer
 * @a_se: previous block's byte size(alt)
 * @n_se: new block's byte size (neu)
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *pn, unsigned int a_se, unsigned int n_se)
{
	char *x;

	if (!pn)
		return (malloc(n_se));
	if (!n_se)
		return (free(pn), NULL);
	if (n_se == a_se)
		return (pn);

	x = malloc(n_se);
	if (!x)
		return (NULL);

	a_se = a_se < n_se ? a_se : n_se;
	while (a_se--)
		x[a_se] = ((char *)pn)[a_se];
	free(pn);
	return (x);
}
