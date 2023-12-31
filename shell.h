#ifndef _SHELL_H_
#define _SHELL_H_

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

/* This is for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* This is for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* This is for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - This is the singly linked list
 * @num: this is the number field
 * @str: This is a string
 * @next: This points to the next node
 */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

/**
 * struct passinfo - This contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: string path for the current command
 * @argc:This is the argument count
 * @line_count: This is the error count
 * @err_num: This is the error code for exit()s
 * @linecount_flag: This is if on count this line of input
 * @fname: This is the program filename
 * @env: This is the linked list local copy of environ
 * @environ: Thsi is the custom modified copy of environ from LL env
 * @history: This the history node
 * @alias: This the alias node
 * @env_changed: This is on if environ was changed
 * @status: This is the return status of the last exec'd command
 * @cmd_buf: This is an address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type:The  CMD_type ||, &&, ;
 * @readfd: This the fd from which to read line input
 * @histcount: This is the history line number count
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

    char **cmd_buf;   /* pointer to cmd ; chain buffer, for memory mangement */
    int cmd_buf_type; /* CMD_type ||, &&, ; */
    int readfd;
    int histcount;
} info_t;

#define INFO_INIT                                                               \
    {                                                                           \
        NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
            0, 0, 0                                                             \
    }

/**
 * struct builtin - This contains a builtin string and related function
 * @type: This is the builtin command flag
 * @func: This is the function
 */
typedef struct builtin
{
    char *type;
    int (*func)(info_t *);
} builtin_table;

/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delimeter(char c, char *delim);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t input_bufffer(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void init_info(info_t *);
void set_info(info_t *, char **);
void release_info(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _my_environment(info_t *);
int _my_setenv(info_t *);
int _my_unsetenv(info_t *);
int calculate_env_list(info_t *);

/* toem_getenv.c */
char **get_environment(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_files(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists_a.c */
list_t *add_node_begining(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void release_list(list_t **);

/* toem_lists_b.c */
size_t list_length(const list_t *);
char **list_of_strings(list_t *);
size_t print_lists(const list_t *);
list_t *start_node_is(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_delim_chain(info_t *, char *, size_t *);
void check_delim(info_t *, char *, size_t *, size_t, size_t);
int replace_alias_token(info_t *);
int replace_variables(info_t *);
int replace_string(char **, char *);

#endif
