#ifndef _SHELL_H_
#define _SHELL_H_

#define MAX_ARGS 100
#define MAX_PATH_LENGTH 100
extern char **environ;

#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdarg.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

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

char **str_tok(char *str, char *delim, int *count);
int check_status(char *path, struct stat *buf);
int execute_(char *command, char **argv, char **env);
void handle_pid_error(pid_t pid);
char *find_command(const char *command);
char *strdup_(const char *str);
char *strchr_(char *str, char c);
void exit_command(int status);
void execute_shell_command(char *command, char **argv, char **env);
ssize_t getline_(char **lineptr, size_t *n, FILE *stream);
size_t tokens_count(char *tokens);
char *strtok_(char *srcString, char *delim);
size_t strlen_(const char* str);
unsigned int is_delim(char c, char *delim);
void pstring(char *s, int nline);
int _putchar(char c);
int _strcmp_(char *s1, char *s2);
int _strlent(char *s);
char **_tok_(int toks, char *s, const char *delim);
void cd_function(char *input);
char *find_dir(char **path_arr, char *command);
char **tok_link(char *line, const char *delim, int toks);
int tok_count(char *line, const char *delim);
void _free_(char **doublepointer);
void _free(int num, ...);
char **_pathtok(int i, char *s);
int _paths(char *var);
char *set_path(char *command);
char *comb_path(char *dir, char *command);
int env_index(char *var);
void env_function(char *s);
void (*function_check(char *s))(char *s);
int inbuilt_functions(char **arguments, char *s);
void exit_function(char *s);
/* ENV */
char *_getenv(const char *name);
void print_path_directories(void);
int _setenv(const char *name, const char *value, int overwrite);

typedef struct PathNode {
    char *directory;
    struct PathNode *next;
} PathNode;
typedef struct builtin {
    char *type;
    int (*func)();
} builtin_commands;

#endif /* _SHELL_H_ */

