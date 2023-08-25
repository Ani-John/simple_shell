#include "shell.h"

char **_pathtok(int i, char *s);
int env_index(char *var);
char *set_path(char *command);
char *comb_path(char *dir, char *command);

/**
 * _pathtok - a function that tokenize path
 * @i: Indexing path in environment
 * @s: tokenize string
 *
 * Return: array of pointer to the string on success else null
 */
char **_pathtok(int i, char *s)
{
	char *env_value;
	int count;
	const char *delim;
	char **_toks;
	int lent;

	delim = ":\n";
	lent = _strlent(s);
	count = 0;
	env_value = environ[i] + (lent + 1);
	_toks = tok_link(env_value, delim, count);
	if (_toks == NULL)
		return (NULL);
	return (_toks);
}

/**
 * env_index - gets index of an environmental variable
 * @var: the variable
 *
 * Return: on success, returns the index holding the
 * variable, else -1
 */
int env_index(char *var)
{
	int a, b, lent;

	lent = _strlent(var);
	for (a = 0; environ[a] != NULL; a++)
	{
		for (b = 0; b < lent; b++)
		{
			if (environ[a][b] != var[b])
				break;
		}
		if (b == lent && environ[a][b] == '=')
			return (a);
	}
	return (-1);
}

/**
 * set_path - sets the path of the program for functions
 * @command: commands passed
 *
 * Return: full path of the prorogram on success, else NULL
 */
char *set_path(char *command)
{
	char *s, *new, *dir;
	char **tokens;
	int d;

	s = "PATH";
	d = env_index(s);
	tokens = _pathtok(d, s);
	if (tokens == NULL)
		return (NULL);
	dir = find_dir(tokens, command);
	if (dir == NULL)
	{
		_free_(tokens);
		return (NULL);
	}

	new = comb_path(dir, command);
	if (new == NULL)
	{
		_free_(tokens);
		return (NULL);
	}
	_free_(tokens);

	return (new);
}

/**
 * comb_path - Combines path directory with command file.
 * @dir: directory
 * @command: command
 *
 * Return: command path, else NULL.
 */
char *comb_path(char *dir, char *command)
{
	int a, b, dirlent, commandlent, lent;
	char *path;

	if (dir == NULL || command == NULL)
		return (NULL);
	dirlent = _strlent(dir) + 1;
	commandlent = _strlent(command) + 1;
	lent = dirlent + commandlent;

	path = malloc(sizeof(char) * lent);
	if (path == NULL)
		return (NULL);

	for (a = 0; a < lent; a++)
	{
		for (b = 0; dir[b] != '\0'; b++, a++)
			path[a] = dir[b];
		path[a] = '/';
		a++;
		for (b = 0; command[b] != '\0'; b++, a++)
			path[a] = command[b];
	}
	path[--a] = '\0';
	return (path);
}
