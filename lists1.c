#include "shell.h"

/**
 * l_ln - determines length of linked list
 * @f: frst nd ptr
 *
 * Return: size of list
 */
size_t l_ln(const list_t *f)
{
	size_t x = 0;

	while (f)
	{
		f = f->next;
		x++;
	}
	return (x);
}

/**
 * l_str - returning strings' arr of l_str
 * @hd: frst nd ptr
 *
 * Return: strings' arr
 */
char **l_str(list_t *hd)
{
	list_t *nd = hd;
	size_t x = l_ln(hd), y;
	char **stngs;
	char *strng;

	if (!hd || !x)
		return (NULL);
	stngs = malloc(sizeof(char *) * (x + 1));
	if (!stngs)
		return (NULL);
	for (x = 0; nd; nd = nd->next, x++)
	{
		strng = malloc(s_lngth(nd->stng) + 1);
		if (!strng)
		{
			for (y = 0; y < x; y++)
				free(stngs[y]);
			free(stngs);
			return (NULL);
		}

		strng = st_coo(strng, nd->stng);
		stngs[x] = stng;
	}
	stngs[x] = NULL;
	return (stngs);
}

/**
 * p_lst - prints all elements of a list_t linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t p_lst(const list_t *hd)
{
	size_t x = 0;

	while (hd)
	{
		st_inp(convert_number(hd->nmbr, 10, 0));
		_putchar(':');
		_putchar(' ');
		st_inp(hd->stng ? hd->stng : "(nil)");
		st_inp("\n");
		hd = hd->next;
		x++;
	}
	return (x);
}

/**
 * sw_nd - returns node of prefix string
 * @nd: L head pointer
 * @px: matching string
 * @c: char following the prefix
 *
 * Return: match node or null
 */
list_t *sw_nd(list_t *nd, char *px, char c)
{
	char *pin = NULL;

	while (nd)
	{
		pin = stw_sherry(nd->stng, px);
		if (pin && ((c == -1) || (*pin == c)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * g_nx - func's prps fetching node's index
 * @hd: L head pointer
 * @nd: node pointer
 *
 * Return: node's index or -1
 */
ssize_t g_nx(list_t *hd, list_t *nd)
{
	size_t x = 0;

	while (hd)
	{
		if (hd == nd)
			return (x);
		hd = hd->next;
		x++;
	}
	return (-1);
}
