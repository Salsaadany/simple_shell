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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @nmbr: the number field
 * @stng: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int nmbr;
	char *stng;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
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

	char **cmd_buf;	  /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* shloop.c --done */
int hsh(info_t *, char **);
int l_bn(info_t *);
void l_exmd(info_t *);
void dev_xmd(info_t *);

/* parser.c --done */
int ex_cd(info_t *, char *);
char *d_chrt(char *, int, int);
char *l_pt(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);
int l_bn(info_t *);
void l_exmd(info_t *);
void dev_xmd(info_t *);

/* errors.c --done */
void eputs_maati(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string.c --done */
int s_lngth(char *);
int s_com(char *, char *);
char *stw_sherry(const char *, const char *);
char *st_conc(char *, char *);

/* string1.c */
char *st_coo(char *, char *);
char *st_dpl(const char *);
void st_inp(char *);
int _putchar(char);

/* exits.c */
char *strncpy_maati(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer.c --done */
char **sp_rep(char *, char *);
char **sp_litter(char *, char);

/* realloc.c --done */
char *st_m(char *, char, unsigned int);
void f_mp(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c --done */
int f_brdm(void **);

/* atoi.c --done */
int maati(info_t *);
int d_islem(char, char *);
int isalpha(int);
int _atoi(char *);

/* errors1.c */
int erratoi_maati(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin.c */
int myexit(info_t *);
int _mycd(info_t *);
int myhelp(info_t *);

/* builtin1.c */
int myhistory_maati(info_t *);
int _myalias(info_t *);

/* getline.c */
ssize_t get_input_lines(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void clear_information(info_t *);
void set_information(info_t *, char **);
void free_information(info_t *, int);

/* environ.c */
char *g_nv(info_t *, const char *);
int myenv_maati(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* getenv.c */
char **get_environ_maati(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c */
char *get_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* lists.c --done */
list_t *a_nd(list_t **, const char *, int);
list_t *a_nnd(list_t **, const char *, int);
size_t p_lst_stng(const list_t *);
int dl_nd(list_t **, unsigned int);
void x_lst(list_t **);

/* lists1.c --done */
size_t l_ln(const list_t *);
char **l_str(list_t *);
size_t p_lst(const list_t *);
list_t *sw_nd(list_t *, char *, char);
ssize_t g_nx(list_t *, list_t *);

/* vars.c */
int ch_del(info_t *, char *, size_t *);
void ch_checker(info_t *, char *, size_t *, size_t, size_t);
int al_rep(info_t *);
int ve_rep(info_t *);
int st_rpl(char **, char *);

#endif
