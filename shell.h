#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#define PROMPT "$ "


/*MACROS */
#define BUFF_SIZE 1024
#define INVALID 22
/**
 * struct in_builts - defining the inbuilt functions
 * @built: name of the command built in
 * @f: pointer to the inbuilt function to call
 */

typedef struct in_builts
{
		char *built;
		void (*f)(char *);
} in_builts_t;

extern char **environ;
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strtok(char *str, const char *delim);

void intilize_argv_to_null(char **argv);
int main(int argc, char **arg);
void pstring(char *s, int nline);
int _putchar(char c);
int _strcmp_(char *s1, char *s2);
int _strlent(char *s);
void _free_(char **doublepointer);
void _free(int num, ...);
void env_function(char *s);
void (*function_check(char *s))(char *s);
int inbuilt_functions(char **arguments, char *s);
void exit_function(char *s);
char **_tok_(int toks, char *s, const char *delim);
void cd_function(char *input);
char *find_dir(char **path_arr, char *command);
char **tok_link(char *line, const char *delim, int toks);
int tok_count(char *line, const char *delim);
char *_strdup_(char *s);
char **_pathtok(int i, char *s);
int env_index(char *var);
char *set_path(char *command);
char *comb_path(char *dir, char *command);
void _errors(char *prog, int com_count, char *commands);
void p_errors(char *prog, int com_count, char *command);
int print_number(int numb);
void parse_(char *list, size_t siz, int commands, char **arg);
void child_(char **param_array, char *list, int commands, char **arg);
void _errors(char *prog, int com_count, char *commands);
void p_errors(char *prog, int com_count, char *command);
int print_number(int numb);

#endif /* SHELL_H */
