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
#include <stropts.h>
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

typedef struct history {
  int id;
  int len;
  char *line;
  char *time;
}              t_hist;

typedef struct s_row {
  int len;
  char *tail;
  char *line;
}               t_row;

typedef struct term_config {
  struct termios origin;
  struct termios raw;
  struct s_row *out;
  int entry;
  int total;
  int *quo;
  int q_id;
  int pos;
  int row;
  int col;
  int x;
  int y;
  int reset;
  int mo_x;
  int mo_y;
  int count;
  char **command;
  char *line;
  char *buf;
}              config;

int main(int argc, char **argv, char **envp);
// int main(void);

#endif
