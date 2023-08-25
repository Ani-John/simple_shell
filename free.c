#include "shell.h"

void _free_(char **doublepointer);
void _free(int num, ...);

/**
 * _free - freeing single pointer
 * @num: number of pointers to free
 */
void _free(int num, ...)
{
	int a;
	char *s;
	va_list num_list;

	va_start(num_list, num);
	for (a = 0; a < num; a++)
	{
		s = va_arg(num_list, char*);
		if (s == NULL)
			continue;
		free(s);
	}
	va_end(num_list);
}

/**
 * _free_ - freeing double pointer
 * @doublepointer: the double pointer
 */
void _free_(char **doublepointer)
{
	int a;

	for (a = 0; doublepointer[a] != NULL; a++)
		free(doublepointer[a]);
	free(doublepointer);
}
