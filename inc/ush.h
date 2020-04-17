#ifndef USH_H
#define USH_H

#define MX_IFMT 0170000
#define MX_ISUID 0004000
#define MX_ISGID 0002000
#define MX_ISVTX 0001000
#define MX_IRUSR 0000400
#define MX_IWUSR 0000200
#define MX_IXUSR 0000100
#define MX_IRGRP 0000040
#define MX_IWGRP 0000020
#define MX_IXGRP 0000010
#define MX_IROTH 0000004
#define MX_IWOTH 0000002
#define MX_IXOTH 0000001

#define MX_IFDIR 0040000
#define MX_IFCHR 0020000
#define MX_IFBLK 0060000
#define MX_IFREG 0100000
#define MX_IFIFO 0010000
#define MX_IFLNK 0120000
#define MX_IFSOCK 0140000

# define MX_FIFO_COL "\x1b[33m"
# define MX_CHR_COL "\x1b[34;43m"
# define MX_DIR_COL "\x1b[1m\x1b[36m"
# define MX_BLK_COL "\x1b[34;46m"
# define MX_REG_COL "\x1b[37;2m"
# define MX_LNK_COL "\x1b[35m"
# define MX_SOCK_COL "\x1b[32m"
# define MX_WHT_COL "\x1b[31m"
# define MX_EXE_COL "\x1b[31m"
# define MX_NONE_COL "\x1b[0m"

#include "libmx/inc/libmx.h"
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_info {
    //struct termios term_old;
    //struct termios term_new;
    char **env;
    char **set;
    char **alias;
    char **commands;
    int status;
    //t_list *history;
    //t_input *input;
    //t_list *processes;
    //bool is_exit;
    //bool if_ctrl_c;
    int exit_status;
    char *pwd;
    char *pwd_l;
    char *pwd_p;
    char *pwd_home;
    char *pwd_old;
    char *path;
    char *home;
    char *cmd;
    //t_list *var_tree;
    //int last_status;
}              t_st;



int main(int argc, char **argv, char **env);
t_st *mx_init_struct(char **env);
void mx_replace_cmd(t_st *st);
void mx_malloc_err();
char **mx_split_line(char *line, int bufsize, int j, int k);
char **mx_split_backup(char **tokens, int bufsize);
void mx_loop(t_st *st);
int mx_simple_commands(t_st *st, char **commands, char *line, int passed_cmd);
int mx_command_pars(t_st *st, char *c, int j, int k);
int mx_streams(t_st *st, char **tokens);
int mx_check_slash(char *line, int end);
char *mx_check_env(char **arr, char *macros);
char *mx_get_env(char *c, int k);
int mx_complex_cmd(t_st *st, char **commands, int i, int passed_cmd);

#endif
