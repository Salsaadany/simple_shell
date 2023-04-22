#include "shell.h"

/**
 * st_coo - copying a given string
 * @terminal: destination
 * @origin: origin
 *
 * Return: pointer to destination
 */
char *st_coo(char *terminal, char *origin)
{
	int x = 0;

	if (terminal == origin || origin == 0)
		return (terminal);
	while (origin[x])
	{
		terminal[x] = origin[x];
		x++;
	}
	terminal[x] = 0;
	return (terminal);
}

/**
 * st_dpl - duplicates a string
 * @st: wannabe duplicated string
 *
 * Return: pointer to the duplicated string
 */
char *st_dpl(const char *st)
{
	int lng = 0;
	char *fix;

	if (slng == NULL)
		return (NULL);
	while (*st++)
		lng++;
	fix = malloc(sizeof(char) * (lng + 1));
	if (!fix)
		return (NULL);
	for (lng++; lng--;)
		fix[lng] = *--st;
	return (fix);
}

/**
 *st_inp - prints an input string
 *@st: wannabe printed string
 *
 * Return: Nothing
 */
void st_inp(char *st)
{
	int x = 0;

	if (!st)
		return;
	while (st[x] != '\0')
	{
		_putchar(st[x]);
		x++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @crc: wannabe displayed char
 *
 * Return: 1 if successful
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char crc)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (crc == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (crc != BUF_FLUSH)
		buf[x++] = crc;
	return (1);
}
