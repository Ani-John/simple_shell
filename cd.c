# include "shell.h"

char **_tok_(int toks, char *s, const char *delim);
void cd_function(char *input);
char *find_dir(char **path_arr, char *command);
char **tok_link(char *line, const char *delim, int toks);
int tok_count(char *line, const char *delim);

/**
 * cd_function - a function that changes directory
 * @input: the input
 */

void cd_function(char *input)
{
	int a, count;
	char **arguments;
	const char *delim;

	delim = "\n\t ";
	count = 0;
	arguments = tok_link(input, delim, count);
	if (arguments[0] == NULL)
	{
		_free(2, arguments, input);
		return;
	}
	if (arguments[1] == NULL)
	{
		a = env_index("HOME");
		chdir((environ[a]) + 5);
	}
	else if (_strcmp_(arguments[1], "-") == 0)
		pstring(arguments[1], 0);

	else
		chdir(arguments[1]);
	_free_(arguments);
}

/**
 * find_dir - a function that finds commands in directories
 * @path_arr: pointer to paths in PATH
 * @command: command passed
 *
 * Return: command file directory on success otherwise NULL.
 */
char *find_dir(char **path_arr, char *command)
{
	int a, b;
	char *wdir;
	char *buf;
	size_t lent;
	struct stat stat_buf;

	buf = NULL;
	lent = 0;
	wdir = getcwd(buf, lent);
	if (wdir == NULL)
		return (NULL);
	if (command[0] == '/')
		command = command + 1;
	for (a = 0; path_arr[a] != NULL; a++)
	{
		b = chdir(path_arr[a]);
		if (b == -1)
		{
			perror("ERROR!");
			return (NULL);
		}
		b = stat(command, &stat_buf);
		if (b == 0)
		{
			chdir(wdir);
			free(wdir);
			return (path_arr[a]);
		}
	}
	chdir(wdir);
	free(wdir);
	return (NULL);
}

/**
 * tok_count - Counts tokens in string passed
 * @line: the string
 * @delim: delimeter
 * Return: count of the tokens on success, otherwise -1.
 */
int tok_count(char *line, const char *delim)
{
	char *s, *toks;
	int a;

	s = _strdup_(line);
	if (s == NULL)
		return (-1);
	toks = strtok(s, delim);
	for (a = 0; toks != NULL; a++)
		toks = strtok(NULL, delim);
	free(s);
	return (a);
}

/**
 * tok_link - a link to other token functions
 * @line: input.
 * @delim: delimeter to tokenize input
 * @toks: counting of tokens
 * Return: the command on successs, otherwise NULL
 */
char **tok_link(char *line, const char *delim, int toks)
{
	char **arguments;

	toks = tok_count(line, delim);
	if (toks == -1)
	{
		free(line);
		return (NULL);
	}
	arguments = _tok_(toks, line, delim);
	if (arguments == NULL)
	{
		free(line);
		return (NULL);
	}

	return (arguments);
}

/**
 * _tok_ - tokenize string
 * @toks: tokens present in string
 * @s: string passsed
 * @delim: the delimeter
 *
 * Return: tokenized string on success, else NULL
 */
char **_tok_(int toks, char *s, const char *delim)
{
	int a;
	char **buf;
	char *tok;
	char *new_string;

	new_string = _strdup_(s);
	buf = malloc(sizeof(char *) * (toks + 1));
	if (buf == NULL)
		return (NULL);
	tok = strtok(new_string, delim);
	for (a = 0; tok != NULL; a++)
	{
		buf[a] = _strdup_(tok);
		tok = strtok(NULL, delim);
	}
	buf[a] = NULL;
	free(new_string);
	return (buf);
}
