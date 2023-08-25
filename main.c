#include "shell.h"

int main(int argc, char **arg);
void parse_(char *list, size_t siz, int commands, char **arg);
void child_(char **param_array, char *list, int commands, char **arg);

/**
 * main - main function
 * @argc: argument count
 * @arg: argument name
 * Return: 0
 */
int main(int argc, char **arg)
{
	char *list;
	size_t siz;
	int commands;
	(void)(argc);

	commands = 0;
	signal(SIGINT, SIG_IGN);
	do {
		commands++;
		list = NULL;
		siz = 0;
		parse_(list, siz, commands, arg);

	} while (1);

	return (0);
}

/**
 * parse_ - Parses the command line looking for commands and argumements.
 * @list: pointer to a string
 * @siz: variable for numbers of size_t
 * @commands: commands entered
 * @arg: Name of the program name
 */
void parse_(char *list, size_t siz, int commands, char **arg)
{
	int a;
	ssize_t len;
	int tok_count;
	char **param_array;
	const char *delim = "\n\t ";

	tok_count = 0;
	write(STDOUT_FILENO, PROMPT, _strlent(PROMPT));
	len = getline(&list, &siz, stdin);
	if (len != -1)
	{
		param_array = tok_link(list, delim, tok_count);
		if (param_array[0] == NULL)
		{
			_free(2, param_array, list);
			return;
		}
		a = inbuilt_functions(param_array, list);
		if (a == -1)
			child_(param_array, list, commands, arg);
		for (a = 0; param_array[a] != NULL; a++)
			free(param_array[a]);
		_free(2, param_array, list);
	}
	else
		exit_function(list);
}

/**
 * child_ - Creates a child program.
 * @param_array: array of pointers
 * @list: The string.
 * @commands: commands entered into the shell.
 * @arg: program name
 */
void child_(char **param_array, char *list, int commands, char **arg)
{
	pid_t new_id;
	int status;
	int a;
	int check;
	struct stat buf;
	char *tmp_;
	char *command;

	new_id = fork();
	if (new_id == 0)
	{
		tmp_ = param_array[0];
		command = set_path(param_array[0]);
		if (command == NULL)
		{
			check = stat(tmp_, &buf);
			if (check == -1)
			{
				p_errors(arg[0], commands, tmp_);
				pstring(": not found", 0);
				_free(2, list, tmp_);
				for (a = 1; param_array[a]; a++)
					free(param_array[a]);
				free(param_array);
				exit(100);
			}
			command = tmp_;
		}
		param_array[0] = command;
		if (param_array[0] != NULL)
		{
			if (execve(param_array[0], param_array, environ) == -1)
				_errors(arg[0], commands, tmp_);
		}
	}
	else
		wait(&status);
}
