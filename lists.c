#include "shell.h"

/**
 * a_nd - func's prpse is node addition to list's beginning
 * @hd: head node pointer's adrs
 * @str: node's strn filed
 * @nmbr: history usage by node's index
 *
 * Return: List's size
 */
list_t *a_nd(list_t **hd, const char *str, int nmbr)
{
	list_t *n_hd;

	if (!hd)
		return (NULL);
	n_hd = malloc(sizeof(list_t));
	if (!n_hd)
		return (NULL);
	st_m((void *)n_hd, 0, sizeof(list_t));
	n_hd->nmbr = nmbr;
	if (str)
	{
		n_hd->stng = st_dpl(str);
		if (!n_hd->stng)
		{
			free(n_hd);
			return (NULL);
		}
	}
	n_hd->next = *hd;
	*hd = n_hd;
	return (n_hd);
}

/**
 * a_nnd - adds a node to the end of the list
 * @hd: address of pointer to head node
 * @str: str field of node
 * @nmbr: node index used by history
 *
 * Return: size of list
 */
list_t *a_nnd(list_t **hd, const char *str, int nmbr)
{
	list_t *n_nd, *nd;

	if (!hd)
		return (NULL);

	nd = *hd;
	n_nd = malloc(sizeof(list_t));
	if (!n_nd)
		return (NULL);
	st_m((void *)n_nd, 0, sizeof(list_t));
	n_nd->nmbr = nmbr;
	if (str)
	{
		n_nd->stng = st_dpl(str);
		if (!n_nd->stng)
		{
			free(n_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = n_nd;
	}
	else
		*hd = n_nd;
	return (n_nd);
}

/**
 * p_lst - display list_t linked list of strng
 * @fn: first node's pntr
 *
 * Return: List's size
 */
size_t p_lst(const list_t *fn)
{
	size_t x = 0;

	while (fn)
	{
		st_inp(fn->stng ? fn->stng : "(nil)");
		st_inp("\n");
		fn = fn->next;
		x++;
	}
	return (x);
}

/**
 * dl_nd - wipes node at given index
 * @hd: first node adrs pointr
 * @ndx: node's indx to be wiped
 *
 * Return: 1 if successful, 0 if not
 */
int dl_nd(list_t **hd, unsigned int ndx)
{
	list_t *nd, *pv_nd;
	unsigned int x = 0;

	if (!hd || !*hd)
		return (0);

	if (!ndx)
	{
		nd = *hd;
		*hd = (*hd)->next;
		free(nd->stng);
		free(nd);
		return (1);
	}
	nd = *hd;
	while (nd)
	{
		if (x == ndx)
		{
			pv_nd->next = nd->next;
			free(nd->stng);
			free(nd);
			return (1);
		}
		x++;
		pv_nd = nd;
		nd = nd->next;
	}
	return (0);
}

/**
 * x_lst - frees all nodes of a list
 * @hd_pt: head node ptr's adrs
 *
 * Return: void
 */
void x_lst(list_t **hd_pt)
{
	list_t *nd, *nx_nd, *hd;

	if (!hd_pt || !*hd_pt)
		return;
	hd = *hd_pt;
	nd = hd;
	while (nd)
	{
		nx_nd = nd->next;
		free(nd->stng);
		free(nd);
		nd = nx_nd;
	}
	*hd_pt = NULL;
}
