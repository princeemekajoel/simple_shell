#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64       /* max number of whitespace/" " */

#define MAX_ARGS 64
#define MAX_PATH 1024
#define DELIMITERS " \t\r\n\a"

extern char **environ;
/**
 * struct linkedList - path linked list
 * @str: path directories
 * @next: pointer to the next node
 */
typedef struct linkedList
{
	char *str;
	struct linkedList *next;
} LL;
/**
 * struct alias_node - alias variables linked list
 * @name: alias name
 * @value: alias value
 * @next: pointer to next node
 */
typedef struct alias_node
{
	char *name;
	char *value;
	struct alias_node *next;
} alias_node;

/* char *read_input(void); */
char *command_checker(char **tokens);
char **parse_input(char *line);
int execute_command(char **args, char *path[]);
void printStr(char *str);
int StringLength(const char *str);
void writeStringToStderr(char *str);
char *get_env(const char *name);
char *concat_Str(char *str1, char *str2);
char *Str_cpy(char *dest, const char *src);
char *Str_cat(char *dest, const char *src);
int Strn_cmp(const char *s1, const char *s2, size_t n);
void *mem_cpy(void *dest, const void *src, size_t n);
void *re_alloc(void *ptr, size_t size);
char **get_path_directories();
int printenv(void);
char *reading_input(void);
int tokenize(char *input, char **tokens, int max_tokens);
void execute(char **tokens);
int my_strcmp(const char *str1, const char *str2);
void execute_builtins(char **tokens, char **env);
char *str_dup(char *str);
char *get_PATH(char *args);
void print_strings(char **strings);
LL *path_list();
void add_node(LL **head_ref, char *str);
void free_list(LL *head);
void print_list(LL *head);
char *finding_executable(char *command, LL *path_list);
char *strd_up(const char *str);

void execute_exit(char **tokens);
void execute_env(char **env);
int execute_cd(char **tokens);

ssize_t my_getline(char **lineptr, size_t *n, int fd);
char *expand_buffer(char *buf, size_t buf_size);
char *allocate_buffer(size_t buf_size);
unsigned int is_delim(char c, char *delim);
char *my_strtok(char *srcString, char *delim);
int is_empty_line(ssize_t len, char *buf);
int handle_empty_line(char *buf, char **lineptr);
void terminate_buffer(ssize_t len, char *buf);
int custom_setenv(const char *name, const char *value, int overwrite);
int custom_unsetenv(const char *name);
int custom_putenv(char *str);
char *custom_strchr(const char *str, int c);
int custom_environSize(void);
void shell_setenv(char **args);
void shell_unsetenv(char **args);
void handle_semicolon(char *input);
int delim_token(char *input, char **tokens, int max_tokens, char *delim);
int logical_operators(char **tokens);
int file_input(int argc, char **argv);

void print_aliases(void);
void alias_command(char **args);

#endif
