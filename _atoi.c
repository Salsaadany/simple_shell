#include "shell.h"

/**
 * mt - if shell is interactive mode return True
 * @n: struct address.
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int mt(info_t *n)
{
	return (isatty(STDIN_FILENO) && n->readfd <= 2);
}

/**
 * d_islem - checks if character is a delimeter
 * @ch: the char to check
 * @ld: the delimeter string
 * Return: 1 if true, 0 if false
 */
int d_islem(char ch, char *ld)
{
	while (*ld)
		if (*ld++ == ch)
			return (1);
	return (0);
}

/**
 * isalpha - checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@st: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *st)
{
	int x, pn = 1, bnr = 0, o_p;
	unsigned int sol = 0;

	for (x = 0;  st[x] != '\0' && bnr != 2; x++)
	{
		if (st[x] == '-')
			pn *= -1;

		if (st[x] >= '0' && st[x] <= '9')
		{
			bnr = 1;
			sol = sol * 10;
			sol = sol + (st[x] - '0');
		}
		else if (bnr == 1)
			bnr = 2;
	}

	if (pn == -1)
		o_p = -sol;
	else
		o_p = sol;

	return (o_p);
}
