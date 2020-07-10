#ifndef USH_H
#define USH_H

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
#include <stdlib.h>
#include <stdio.h>
#include <termcap.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <signal.h>

#define CTRL_KEY(k) ((k) & 0x1f)
#define ABUF_INIT {NULL, 0}
#define MAXBUFSIZE (10000U)
#define MX_BACKSPACE 127
#define MX_DELBUF "\b \b"
#define MX_ARROW_LEFT 1000
#define MX_ARROW_RIGHT 1001
#define MX_ARROW_UP 1002
#define MX_ARROW_DOWN 1003
#define MX_PAGE_UP 1004
#define MX_PAGE_DOWN 1005
#define MX_HOME_KEY 1006
#define MX_END_KEY 1007
#define MX_DEL_KEY 1008

typedef struct s_history {
    int id;
    int len;
    char *line;
}              t_hist;

typedef struct s_row {
    int len;
    char *tail;
    char *line;
}              t_row;

typedef struct s_config {
    struct termios origin;
    struct termios raw;
    struct s_row *out;
    int entry;
    int total;
    int *quo;
    int q_id;
    int pos;
    int x_offset;
    int row;
    int col;
    int x;
    int y;
    int reset;
    int mo_x;
    int mo_y;
    int count;
    int press;
    int num;
    int max_len;
    char **command;
    char **buf;
}               t_config;

int main(int argc, char **argv, char **envp);
void mx_get_commands(t_config *term);
t_config *mx_config_init(void);
void mx_get_term_params(t_config *term);
void mx_loop(t_config* term, t_hist **hist);
void mx_raw_mode_on(void);
void mx_get_cursor(int *y, int *x);
void mx_refresh_line(t_config* term, int offset);
void mx_refresh_screen(t_config* term, int offset);
void mx_cooked_mode_on(void);
void mx_process_key(t_config *term, t_hist **hist);
void mx_qoutes_handling(t_config *term);
void mx_editor_processing(t_config* term, int c);
int mx_read_key(void);
void mx_arrows_motion(int k, t_config* term, t_hist **hist);
void mx_die(const char *str);
void mx_return_action(t_config *term, t_hist **hist);
void mx_tab_action(t_config *term);
void mx_backspace_action(t_config *term);
void mx_clear_screen(t_config* term);
void mx_free_assumptions(t_config *term);
void mx_set_cursor(t_config *term);

//delete these function while merging
char *mx_itoa(int number);
char *mx_strdup(const char *str);
char *mx_strcpy(char *dst, const char *src);
char *mx_strndup(const char *s1, size_t n);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strnew(const int size);

#endif
