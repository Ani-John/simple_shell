#include "shell.h"

void pstring(char *s, int nline);
int _putchar(char c);
int _strcmp_(char *s1, char *s2);
int _strlent(char *s);


/**
 * _putchar - Writes a character to stdout
 * @c:the character
 * Return: characters written.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _strcmp_ - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: 0
 */
int _strcmp_(char *s1, char *s2)
{
	int a;

	if (_strlent(s1) != _strlent(s2))
		return (-1);
	for (a = 0; s1[a] != '\0'; a++)
	{
		if (s1[a] != s2[a])
			return (-1);
	}
	return (0);
}

/**
 * _strlent - getting the lenght of a string
 * @s: the string
 *
 * Return: length of string
 */
int _strlent(char *s)
{
	int a;

	if (s == NULL)
		return (0);
	a = 0;
	do {
		a++;
	} while (s[a] != '\0');
	return (a);
}

/**
 * _strdup_ - duplicating string
 * @s: the string
 *
 * Return: the duplicated string
 */
char *_strdup_(char *s)
{
	int a, lent;
	char *dup;

	lent = _strlent(s);
	dup = malloc(sizeof(char) * (lent + 1));
	if (dup == NULL)
		return (0);
	for (a = 0; s[a] != '\0'; a++)
		dup[a] = s[a];
	dup[a] = '\0';
	return (dup);
}

/**
 * pstring - printing a string
 * @s: the string
 * @nline: new line
 */
void pstring(char *s, int nline)
{
	int a;

	if (s == NULL)
		s = "null";
	a = 0;
	do {
		write(STDOUT_FILENO, &s[a], 1);
		a++;
	} while (s[a] != '\0');
	if (nline == 0)
		write(STDOUT_FILENO, "\n", 1);
}
