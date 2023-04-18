#include "shell.h"

/**
 * f_brdm - freeing pointer and NULLing add
 * @pn: pointer's add
 *
 * Return: 1 if successful, 0 if not.
 */
int f_brdm(void **pn)
{
	if (pn && *pn)
	{
		free(*pn);
		*pn = NULL;
		return (1);
	}
	return (0);
}
