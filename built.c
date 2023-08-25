#include "shell.h"

void env_function(char *s);
void (*function_check(char *s))(char *s);
int inbuilt_functions(char **arguments, char *s);
void exit_function(char *s);

/**
 * function_check - checks for the right function
 * @s: pointer to function
 *
 * Return: needed function or NULL.
 */
void (*function_check(char *s))(char *s)
{
	int a;

	in_builts_t inbuilts[] = {
		{"exit", exit_function},
		{"env", env_function},
		{"printenv", env_function},
		{"cd", cd_function},
		{NULL, NULL}
	};
	for (a = 0; inbuilts[a].built != NULL; a++)
	{
		if (_strcmp_(s, inbuilts[a].built) == 0)
		{
			return (inbuilts[a].f);
		}
	}
	return (NULL);
}

/**
 * inbuilt_functions - gets inbuilt functions
 * @arguments: An array of all the arguments passed to the shell.
 * @s: A string representing the input
 *
 * Return: on succes, 0. return -1 on exit.
 */
int inbuilt_functions(char **arguments, char *s)
{
	void (*function)(char *);

	function = function_check(arguments[0]);
	if (function == NULL)
		return (-1);
if (_strcmp_("exit", arguments[0]) == 0)
_free_(arguments);
function(s);
return (0);
}

/**
 * exit_function - writing an exit function
 * @s: input string
 */
void exit_function(char *s)
{
	free(s);
	pstring("\n", 1);
	exit(1);
}

/**
 * env_function - wrinting wnv functiong
 * @s:  input string
 */
void env_function(char *s)
{
	int a, b;
	(void)(*s);

	for (a = 0; environ[a] != NULL; a++)
	{
		for (b = 0; environ[a][b] != '\0'; b++)
			write(STDOUT_FILENO, &environ[a][b], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}
