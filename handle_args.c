#include "shell.h"
#define BUFFER_SIZE 1024
#define MAX_NUM_ARGUMENTS 100

int check_status(char *path, struct stat *buf)
{
	int value;

	value = stat(path, buf);
	if (value == 0)
		return (0);
	else
		return (1);
}

ssize_t getline_(char **lineptr, size_t *n, FILE *stream)
{

	static char buffer[BUFFER_SIZE];
	size_t line_length = 0;
	char c, *new_lineptr;
	int end_of_file = 0, buffer_size = 0, buffer_pos = 0;

	if (*n == 0 || *lineptr == NULL)
	{
		*n = BUFFER_SIZE;
		*lineptr = malloc(*n);
		if (!*lineptr)
			return (-1);
	}
	while (1)
	{
		if (buffer_pos >= buffer_size)
		{
			buffer_size = read(fileno(stream), buffer, BUFFER_SIZE);
			if (buffer_size == 0)
			{
				end_of_file = 1;
				break;
			}
			buffer_pos = 0;
		}
		if (buffer_size == -1)
			return (-1);
		c = buffer[buffer_pos++];

		if (line_length + 1 >= *n)
		{
			*n *= 2;
			new_lineptr = realloc(*lineptr, *n);

			if (!new_lineptr)
				return (-1);
			*lineptr = new_lineptr;
		}
		(*lineptr)[line_length++] = c;

		if (c == '\n')
			break;
	}
	if (line_length > 0)
	{
		(*lineptr)[line_length] = '\0';
		return (line_length);
	}
	else if (end_of_file)
		return (-1);
	else
		return (0);
}


char *find_command(const char *command)
{
	struct stat buf;
	char *path = _getenv("PATH"), *full_path = NULL;
	char *dir = strtok_(path, ":");
	size_t full_path_length;

	if (path == NULL)
	{
		return (NULL);
	}

	path = strdup_(path);

	while (dir != NULL)
	{
		full_path_length = strlen_(dir) + strlen_(command) + 2;

		full_path = (char *)malloc(full_path_length);

		if (full_path == NULL)
		{
			perror("Memory allocation error");
			exit(1);
		}

		snprintf(full_path, full_path_length, "%s/%s", dir, command);

		if (check_status(full_path, &buf) == 0)
		{
			free(path);
			return (full_path);
		}

		free(full_path);
		dir = strtok_(NULL, ":");
	}

	free(path);
	return (NULL);
}

int execute_(char *command, char **argv, char **env)
{
	/* Check if the provided command already contains a slash '/'*/
	if (strchr(command, '/') != NULL)
	{
		if (execve(command, argv, env) == -1)
		{
			perror("Error!");
			exit(1);
		}
	}
	else
	{
		char *full_command = find_command(command);

		if (full_command == NULL)
		{
			printf("Command not found: %s\n", command);
			exit(1);
		}

		if (execve(full_command, argv, env) == -1)
		{
			perror("Error!");
			exit(1);
		}
	}

	return (0);
}
