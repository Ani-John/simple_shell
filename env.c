#include "shell.h"
/**
 * _getenv - a function that gets the value of an
 * environment variable
 * @name: the name of the environment variable to retrieve
 * Return: on success a pointer to the value of the
 * environment variable on failure NULL
 */
char *_getenv(const char *name)
{
	char **env = environ;
	size_t name_len = strlen_(name);

	while (*env)
	{
		if (strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=')
		{
			return (*env + name_len + 1);
		}
		env++;
	}

	return (NULL);
}
/**
 * _setenv - sets or updates an environment variable
 * @name: the name of the environment variable to set
 * @value: the value to be assigned to the environment
 * variable
 * @overwrite: a flag that indicates if an existing variable
 * should be overwritten or not
 * Return: on success 0, on failure -1
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	size_t name_len = strlen_(name);
	size_t value_len = strlen_(value);
	char *old_value = _getenv(name), *new_env, **new_environ;
	int environ_size, i, j;

	if (!name || !value || (old_value && !overwrite))
		return (-1);
	new_env = malloc(name_len + value_len + 2);

	if (!new_env)
		return (-1);
	snprintf(new_env, name_len + value_len + 2, "%s=%s", name, value);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			free(environ[i]);
			environ[i] = new_env;
			return (0);
		}
	}
	environ_size = 0;

	while (environ[environ_size])
		environ_size++;
	new_environ = malloc((environ_size + 2) * sizeof(char *));

	if (!new_environ)
	{
		free(new_env);
		return (-1);
	}
	for (j = 0; j < environ_size; j++)
		new_environ[j] = environ[j];
	new_environ[environ_size] = new_env;
	new_environ[environ_size + 1] = NULL;

	environ = new_environ;
	return (0);
}


/**
 * print_path_directories - prints the directories
 * listed in the PATH environment
 */

void print_path_directories(void)
{
	char *path = _getenv("PATH");
	char *token = strtok_(path, ":");

	if (path == NULL)
	{
		printf("PATH environment variable not found.\n");
		return;
	}

	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok_(NULL, ":");
	}
}
/**
 * build_path_list - Builds a linked list of directories from the
 * PATH environment variable.
 * Return: a  pointer to the head of the linked list of directories
 */
PathNode *build_path_list(void)
{
	char *path = _getenv("PATH"), *token;
	PathNode *head = NULL;
	PathNode *current = NULL;

	if (path == NULL)
	{
		printf("PATH environment variable not found.\n");
		return (NULL);
	}

	token = strtok_(path, ":");

	while (token != NULL)
	{
		PathNode *node = malloc(sizeof(PathNode));

		if (node == NULL)
		{
			perror("Memory allocation error");
			return (NULL);
		}
		node->directory = strdup_(token);
		node->next = NULL;

		if (current == NULL)
		{
			head = node;
			current = node;
		}
		else
		{
			current->next = node;
			current = node;
		}
		token = strtok_(NULL, ":");
	}
	return (head);
}
/**
 * free_path_list - Frees the memory associated with the
 * linked list of directories
 * @head: a pointer to the head node of the linked list
 * to be freed
 */
void free_path_list(PathNode *head)
{
	while (head != NULL)
	{
		PathNode *temp = head;

		head = head->next;
		free(temp->directory);
		free(temp);
	}
}
