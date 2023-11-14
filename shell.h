#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - Singly linked ls
 * @num: This is the num field
 * @str: This is a str
 * @next: This points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arg to pass into a func allowing uniform prototype for func ptr struct
 *@arg: a string generated from getline containing arguments
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - Contains an assembled/builtin str and related func
 *@type: This is the assembled/builtin command flag
 *@func: This is the func
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* _loop.c */
int hsh(info_t *, char **);
int find_assembled(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* _parser.c */
int is_cmd(info_t *, char *);
char *dup_char(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* _errors.c */
void _puts(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* _string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *start_hay(const char *, const char *);
char *_strcat(char *, char *);

/* _string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* _escape.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* _token.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* _reallocate.c */
char *_memoryset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* _mem.c */
int bfree(void **);

/* _atoi.c */
int collaborative(info_t *);
int is_separator(char, char *);
int alpha(int);
int _atoi(char *);

/*_errors1.c */
int _erroratoi(char *);
void print_err(info_t *, char *);
int print_d(int, int);
char *convert_num(long int, int, int);
void rem_comments(char *);

/* _assemble1.c */
int _myescape(info_t *);
int _mycd(info_t *);
int _myassist(info_t *);

/* _assemble2.c */
int _mypast(info_t *);
int _myalias(info_t *);

/* _getline.c */
ssize_t get_inputs(info_t *);
int _getlines(info_t *, char **, size_t *);
void siginthandler(int);

/* _getinformation.c */
void clear_infor(info_t *);
void set_infor(info_t *, char **);
void free_infor(info_t *, int);

/* _environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int pop_env_list(info_t *);

/* _getenv.c */
char **get_environment(info_t *);
int _unsetenv(info_t *, char *);
int _setenvironment(info_t *, char *, char *);

/* _past.c */
char *get_past_file(info_t *info);
int write_past(info_t *info);
int read_past(info_t *info);
int build_past_list(info_t *info, char *buf, int linecount);
int renumber_past(info_t *info);

/* _lists1.c */
list_t *add_nodes(list_t **, const char *, int);
list_t *add_nodes_end(list_t **, const char *, int);
size_t print_ls_str(const list_t *);
int del_node_at_index(list_t **, unsigned int);
void free_ls(list_t **);

/* _lists2.c */
size_t ls_len(const list_t *);
char **ls_to_str(list_t *);
size_t print_ls(const list_t *);
list_t *node_starts(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* _var.c */
int is_chain(info_t *, char *, size_t *);
void check_chains(info_t *, char *, size_t *, size_t, size_t);
int rep_alias(info_t *);
int rep_var(info_t *);
int rep_str(char **, char *);

#endif
