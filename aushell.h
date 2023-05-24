#ifndef _AUSHELL_H_
#define _AUSHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define EXIT -3
#define HOME "AUshell $ "
#define E_O_F -2

/* Global int variable */
int history;
/* Global char variable */
char *command_name;
/* Global environemnt */
extern char **environ;

/**
 * struct builtin - A user defined variable for builtin.
 * @name: The name of the builtin command.
 * @func: function pointer.
 */
typedef struct builtin
{
	char *name;
	int (*func)(char **argv, char **node);
} builtin_t;

/**
 * struct mylist - A user-defined variable for list.
 * @dir: variable for dir path.
 * @next: varible for pointer to the next node.
 */
typedef struct mylist
{
	char *dir;
	struct mylist *next;
} list_t;

/**
 * struct alias - A new struct defining aliases.
 * @name: variable for name of the alias.
 * @value: varible forvalue of the alias.
 * @next: variable to next node.
 */
typedef struct alias
{
	char *name;
	char *value;
	struct alias *next;
} Alias;

/* For Alias */
Alias *myalias;

/* Custom builtins */
int (*get_builtin(char *cmd))(char **argv, char **node);
int my_exit(char **argv, char **node);
int my_env(char **argv, char **node);
int my_setenv(char **argv, char **node);
int my_unsetenv(char **argv, char **node);
int my_cd(char **argv, char **node);
int my_help(char **argv, char **node);

/* Line Functions */
ssize_t my_getline(char **ptr_line, size_t *num, FILE *stream);
void assign_ptr(char **ptr_line, size_t *num, char *buf, size_t buffer_size);
void *my_realloc(void *prev_mem, unsigned int old_byte, unsigned int new_byte);

/* File Functions */
int disply_open_error(char *file_path);
int file_pro_cmd(char *file_path, int *exit_code);

/* Path Handlers*/
char *fill_path_buf(char *path_tokens);
list_t *get_path(char *env_name);
char *find_executable_path(char *command);

/* AUshell.c */
void sig_handler(int signal_num);
int shell_run(char **command_args, char **orginal_args);

/*Convertions*/
char *my_itoa(int size);
int make_errors(char **argv, int error_no);
int num_length(int size);

/* Argument functions */
int call_args(char **argv, char **node, int *exec_ret);
char *read_args(char *input, int *exec_ret);
int exec_args(char **args, char **, int *exec_ret);
int verify_args(char **argv);
int perform_args(int *exec_ret);

/* String functions */
char *str_cpy(char *dest, const char *src);
char *str_cat(char *dest, const char *src);
char *strn_cat(char *dest, const char *src, size_t num);
int str_len(const char *str);

char *str_chr(char *str, char ch);
int str_spn(char *str, char *prefix);
int str_cmp(char *str1, char *str2);
int strn_cmp(const char *str1, const char *str2, size_t num);

/* Token functions */
int find_delim(char *str, char *delimit);
int token_count(char *str, char *delimit);
char **my_strtok(char *input, char *delimit);

/* Environment Helpers */
void free_env(void);
char **copy_environ(void);
char **my_getenv(const char *name);

/* Alias Builtin */
int my_alias(char **argv, char **node);
void rename_alias(char *variable_name, char *value);
void display_alias(Alias *alias);
char **replace_alias(char **argv);

/* Error Handling */
char *env_error(char **argv);
char *alias_error(char **argv);
char *exit_error(char **argv);
char *cd_error(char **argv);

char *syntax_error(char **argv);
char *error_msg_126(char **argv);
char *error_msg_127(char **argv);

/* Alias Utilites */
list_t *add_node_end(list_t **head, char *dir_path);
void free_node(list_t *head);
Alias *add_alias_node(Alias **head, char *name, char *value);
void free_alias_node(Alias *alias_head);

/* Helper Functions*/
void get_operator(char *input, ssize_t *new_size);
ssize_t cal_new_size(char *input);
void check_line(char **input, ssize_t line_len);

void free_args(char **argv, char **node);
char *my_getpid(void);
char *get_env_var(char *start, int length);
void replace_var(char **argv, int *exec_ret);

/* Help Utilites */
void all_help(void);
void alias_help(void);
void cd_help(void);
void exit_help(void);
void helps_help(void);

void env_help(void);
void setenv_help(void);
void unsetenv_help(void);
void history_help(void);

#endif /* _AUSHELL_H_ */

