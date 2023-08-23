#include "shell.h"
#define BUFFER_SIZE 64
/**
 * handle_pid_error - handle errors relating
 * to process ID
 * @pid: the pid to handle
 */
void handle_pid_error(pid_t pid)
{
	if (pid == -1)
	{
		perror("Error!");
		exit(1);
	}
}

/**
 * is_delim - checks if a character is
 * a delimiter
 * @c: the character to be checked
 * @delim: A pointer to a null-terminated string of
 * delimiter characters
 * Return: 1 if it is a delimiter else return 0
 */

unsigned int is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * execute_shell_command - executes a shell command
 * @command: the command to be executed
 * @argv: an array of strings representing the command arguments
 * @env: an array od strings representing the environment variable
 */

void execute_shell_command(char *command, char **argv, char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	handle_pid_error(pid);

	if (pid == 0)
	{
		execute_(command, argv, env);
		exit(0);
	}

	if (wait(&status) == -1)
	{
		perror("Error!");
		exit(1);
	}
}
