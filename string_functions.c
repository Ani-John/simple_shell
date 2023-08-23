#include "shell.h"
/**
 * strdup_ - this function duplicates a string in memory
 * @str: the string to be duplicated
 * Return: a pointer to the duplicated string
 * or NULL if the process fails
 */
char *strdup_(const char *str)
{
	size_t len;
	char *copy;

	if (str == NULL)
	{
		return (NULL);
	}

	len = strlen(str);
	copy = (char *)malloc(len + 1);

	if (copy != NULL)
	{
		strcpy(copy, str);
	}
	return (copy);
}

/**
 * strchr_ - a function that locates
 * the first occurence of a particular character
 * in a string
 * @str: the string to be checked
 * @c: the character to be checked for
 * Return: a pointer to the first occurence
 * of the character the string or NULL if not found
 */

char *strchr_(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * strtok_ - A split function that splits a string into an array of substrings
 * based on separator characters
 * @srcString: the source string
 * @delim: the delimiter by which the string will be separated
 * Return: The strings separated
 */
char *strtok_(char *srcString, char *delim)
{
	static char *backup_string, *ret;

	if (!srcString)
		srcString = backup_string;
	if (!srcString)
		return (NULL);

	while (1)
	{
		if (is_delim(*srcString, delim))
		{
			srcString++;
			continue;
		}
		if (*srcString == '\0')
			return (NULL);
		break;
	}
	ret = srcString;
	while (1)
	{
		if (*srcString == '\0')
		{
			backup_string = srcString;
			return (ret);
		}
		if (is_delim(*srcString, delim))
		{
			*srcString = '\0';
			backup_string = srcString + 1;
			return (ret);
		}
		srcString++;
	}
}

/**
 * strlen_ - a function that returns the length of a string
 * @str: the string to be counted
 * Return: length of the string
 */

size_t strlen_(const char *str)
{
	size_t len = 0;

	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}
