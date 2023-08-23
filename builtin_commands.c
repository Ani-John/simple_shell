#include "shell.h"

/**
 * exit_command - function that exits the shell
 * @status: an argument that can be passed with
 * the exit command
 */

void exit_command(int status)
{
	printf("Exiting the shell...\n");
	exit(status);
}




