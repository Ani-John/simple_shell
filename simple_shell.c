#include "shell.h"
/**
 * main - the main function for the simple shell program
 * @argc: number of arguments passed
 * @av: the arguments passed
 * @env: the environment variable
 * Return: always 0
 */

int main(int argc, char **av, char **env)
{
	size_t bufferSize = 0;
	ssize_t bytesRead;
	char *prompt = "$ ", *input = NULL, *token, *args[MAX_ARGS];

	while (true)
	{
		if (isatty(STDIN_FILENO) != 0)
			write(STDOUT_FILENO, prompt, strlen_(prompt));
		bytesRead = getline_(&input, &bufferSize, stdin);

		if (bytesRead == -1)
		{
			perror("Error!");
			free(input);
			exit(1);
		}
		if (input[bytesRead - 1] == '\n')
			input[bytesRead - 1] = '\0';

		argc = 0;

		token = strtok_(input, " ;\n");
		while (token != NULL)
		{
			args[argc++] = token;
			token = strtok_(NULL, " ;\n");
		}
		args[argc] = NULL;
		if (argc > 0 && ((strcmp(args[0], "exit") == 0) || strcmp(*av, "exit") == 0))
		{
			int exit_status = (argc > 1) ? atoi(args[1]) : 0;

			free(input);
			exit_command(exit_status);
		}
		if (argc > 0)
			execute_shell_command(args[0], args, env);
	}
	free(input);
	return (0);
}
