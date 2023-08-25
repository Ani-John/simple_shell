#include "shell.h"

void _errors(char *prog, int com_count, char *commands);
void p_errors(char *prog, int com_count, char *command);
int print_number(int numb);

/**
 * _errors - a function that prints exec errors
 * @prog: program name
 * @com_count: command count
 * @commands: command
 */

void _errors(char *prog, int com_count, char *commands)
{
	p_errors(prog, com_count, commands);
	pstring(": ", 1);
	perror("");
	exit(1);
}

/**
 * p_errors - Prints a message error when a comand is not found.
 * @com_count: command count
 * @prog: The name of the program
 * @command: command not being found.
 */
void p_errors(char *prog, int com_count, char *command)
{
	pstring(prog, 1);
	pstring(": ", 1);
	print_number(com_count);
	pstring(": ", 1);
	pstring(command, 1);
}

/**
 * print_number - Printing unsigned number
 * @numb: the number
 *
 * Return: The amount of numbers printed
 */
int print_number(int numb)
{
	int div = 1;
	int lent = 0;
	unsigned int num;

	div = 1;
	lent = 0;

	num = numb;

	for (; num / div > 9; )
		div *= 10;

	for (; div != 0; )
	{
		lent += _putchar('0' + num / div);
		num %= div;
		div /= 10;
	}

	return (lent);
}
