#include "ush.h"
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <termcap.h>
#include <term.h>
#include <curses.h>
#include <ctype.h>

char *mx_strnew(const int size) {
    char *s = NULL;

    if (size < 0) 
        return NULL;
    s = (char *)malloc(size + 1);
    if (s != 0) 
        for(int i = 0; i <= size; i++)
            s[i]= '\0';
    return s;
}

char *mx_strncpy(char *dst, const char *src, int len) {
    int i = 0;

    for (; src[i] != '\0' && i < len; i++)
        dst[i] = src[i];
    for (; i < len; i++)
        dst[i] = '\0';
    return dst;
}

char *mx_strndup(const char *s1, size_t n) {
    size_t len = strlen(s1);

    if (len <= n)
        return mx_strncpy(mx_strnew(len), s1, n);
    return mx_strncpy(mx_strnew(n), s1, n);
}

char *mx_strcpy(char *dst, const char *src) {
    int i = 0;

    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return dst;
}

char *mx_strdup(const char *str) {
    return mx_strcpy(mx_strnew(strlen(str)), str);
}

static int count_len(int number) {
    int len = 1;

    if (number < 0) {
        if (number == -2147483648) {
            number = -147483648;
            len = 2;
        }
        number = -number;
    }
    else if (number > 0)
        len = 0;
    while (number > 0) {
        len++;
        number /= 10;
    }
    return len;
}

char *mx_itoa(int number) {
    char *str = NULL;
    int len = count_len(number);

    str = mx_strnew(len);
    if (number == 0)
        str[0] = '0';
    if (number < 0) {
        str[0] = '-';
        if (number == -2147483648) {
            str[1] = '2';
            number = -147483648;
        }
        number = -number;
    }
    for (; number > 0; number /= 10) {
        len--;
        str[len] = (number % 10) + 48;
    }
    return str;
}


void die(const char *str) {
  perror(str);
  exit(1);
}

void cooked_mode_on() {
  struct termios raw;

  if (tcsetattr(STDIN_FILENO, TCSADRAIN, &raw) == -1)
    die("tcsetattr");
}

void raw_mode_on() {
  struct termios raw;

  tcgetattr(STDIN_FILENO, &raw);
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void get_cursor(int *y, int *x) {
 char buf[30];
 int i;
 char ch;

 write(1, "\033[6n", 4);
 for (i = 0, ch = 0; ch != 'R'; i++ )
 {
    read(0, &ch, 1);
    buf[i] = ch;
 }
 sscanf(&buf[2], "%d;%d", x, y);
}

void refresh_screen(config* term, int offset) {
  write(1, "\x1b[", 2);
  write(1, mx_itoa(term->mo_x + term->x_offset), strlen(mx_itoa(term->mo_x + term->x_offset)));
  write(1, ";", 1);
  write(1, mx_itoa(term->mo_y + offset), strlen(mx_itoa(term->mo_y + offset)));
  write(1, "H", 1);
}

// void process_output(config *term) {
//   if (term->pos)
//     term->mo_y = -5;
//     term->pos = 0;
//     term->out->len = 0;
//   if (strlen(term->out->line)) {
//     write(1, "\r\n", 2);
//     write(1, term->out->line, strlen(term->out->line));
//     write(1, "\r\n", strlen("\r\n"));
//   }
// }

void refresh_line(config* term, int offset) {
  term->mo_y = 1;
  write(1, "u$h> ", strlen("u$h> "));
  write(1, "\x1b[", 2);
  write(1, mx_itoa(term->mo_x  + term->x_offset), strlen(mx_itoa(term->mo_x  + term->x_offset)));
  write(1, ";", 1);
  write(1, mx_itoa(term->mo_y + offset), strlen(mx_itoa(term->mo_y + offset)));
  write(1, "H", 1);
}

void arrows_motion(int k, config* term, t_hist **hist) {
  switch (k) {
    case MX_ARROW_LEFT:
    if (term->mo_y > 1)
      term->mo_y--;
    break;
    case MX_ARROW_RIGHT:
    if (term->mo_y < term->out->len + 1)
      term->mo_y++;
    break;
    case MX_ARROW_UP:
      if (term->total > 0 && hist[term->total - 1]) {
        if (term->out->line != NULL) {
          free(term->out->line);
          term->out->len = 0;
        }
        term->out->line = mx_strndup(hist[term->total - 1]->line, hist[term->total - 1]->len);
        term->out->len = hist[term->total - 1]->len;
        write(1, "\r", 1);
        refresh_line(term, 5);
        write(1, hist[term->total - 1]->line, hist[term->total - 1]->len);
        write(1, "\x1b[0J", strlen("\x1b[0J"));
        term->mo_y = hist[term->total - 1]->len + 1;
        term->total--;
      }
    break;
    case MX_ARROW_DOWN:
      if (term->total < term->entry - 1) {
        if (term->out->line != NULL) {
          free(term->out->line);
          term->out->len = 0;
        }
        term->out->line = mx_strndup(hist[term->total + 1]->line, hist[term->total + 1]->len);
        term->out->len = hist[term->total + 1]->len;
        write(1, "\r", 1);
        refresh_line(term, 5);
        write(1, hist[term->total + 1]->line, hist[term->total + 1]->len);
        write(1, "\x1b[0J", strlen("\x1b[0J"));
        term->mo_y = hist[term->total + 1]->len + 1;
        term->total++;
      }
      else if (term->total < term->entry) {
         if (term->out->line != NULL) {
          free(term->out->line);
          term->out->len = 0;
        }
        write(1, "\r", 1);
        refresh_line(term, 5);
        write(1, "\x1b[0J", strlen("\x1b[0J"));
        term->mo_y = 1;
      }
    break;
  }
}

int readKey(config *term) {
  (void)term;
  int nread;
  char c;
  char arr[3];

  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1)
      die("read");
  }
  if (c == '\x1b') {
    if (read(STDIN_FILENO, &arr[0], 1) != 1)
      return '\x1b';
    if (read(STDIN_FILENO, &arr[1], 1) != 1)
      return '\x1b';
    if (arr[0] == '[') {
      if (arr[1] >= '0' && arr[1] <= '9') {
        if (read(STDIN_FILENO, &arr[2], 1) != 1)
          return '\x1b';
        if (arr[2] == '~') {
          switch(arr[1]) {
            case '1': return MX_HOME_KEY;
            case '3': return MX_DEL_KEY;
            case '4': return MX_END_KEY;
            case '5': return MX_PAGE_UP;
            case '6': return MX_PAGE_DOWN;
            case '7': return MX_HOME_KEY;
            case '8': return MX_END_KEY;
          }
        }
      }
      else {
          switch(arr[1]) {
            case 'A': return MX_ARROW_UP;
            case 'B': return MX_ARROW_DOWN;
            case 'C': return MX_ARROW_RIGHT;
            case 'D': return MX_ARROW_LEFT;
            case 'H': return MX_HOME_KEY;
            case 'F': return MX_END_KEY;
          }
      }
    }
    else if (arr[0] == 'O') {
      switch (arr[1]) {
        case 'H': return MX_HOME_KEY;
        case 'F': return MX_END_KEY;
      }
    }
    return '\x1b';
  }
  else
    return c;
}

void editor_processing(config* term, int c) {
  if (term->mo_y - 1 < term->pos) {
        term->out->tail = mx_strndup(term->out->line + term->mo_y - 1, term->out->len - term->mo_y + 1);
        term->pos = term->mo_y - 1;
  }
  else if (term->mo_y - 1 == term->out->len) {
    term->pos = term->mo_y - 1;
    free(term->out->tail);
    term->out->tail = NULL;
  }
  else if (term->mo_y - 1 > term->pos && term->mo_y - 1 < term->out->len) {
        term->out->tail = mx_strndup(term->out->line + term->mo_y - 1, term->out->len - term->mo_y + 1);
        term->pos = term->mo_y - 1;
  }
    term->out->len++;
    term->out->line[term->pos++] = c;
    write(STDIN_FILENO, &c, 1);
    if (term->out->tail != NULL) {
      term->out->line = realloc(term->out->line, term->out->len);
      memcpy(term->out->line + term->pos, term->out->tail, strlen(term->out->tail));
      write(STDIN_FILENO, term->out->tail, strlen(term->out->tail));
    }
    term->mo_y++;
}

void qoutes_handling(config *term) {
  for (int i = 0; i < term->out->len; i++)
  if (term->quo[0] != 96 && term->quo[1] != 96) {
    if (!term->quo[0] && (term->out->line[i] == 34 || term->out->line[i] == 39))
      term->quo[term->q_id++] = term->out->line[i];
    else if (term->out->line[i] == 96)
      term->quo[term->q_id++] = term->out->line[i];
    else if (term->quo[0] == term->out->line[i]) {
      term->quo[0] = 0;
      term->q_id--;
    }
  }
  else if (term->quo[0] == 96 && term->quo[0] == term->out->line[i]) {
    term->quo[0] = 0;
    term->q_id--;
  }
  else if (term->quo[1] == term->out->line[i]) {
    term->quo[1] = 0;
    term->q_id--;
  }
}

void processKey(config *term, t_hist **hist) {
  int c = readKey(term);

  switch (c) {
    case '\r':
      if (term->out->len > 0) {
        qoutes_handling(term);
        if (!hist[term->entry]) {
          hist[term->entry] = (t_hist *)malloc(sizeof(t_hist) * 1);
          hist[term->entry]->id = term->entry;
          hist[term->entry]->len = term->out->len;
          hist[term->entry]->line = mx_strndup(term->out->line, term->out->len);
        } else {
          hist[term->entry]->line = realloc(hist[term->entry]->line, hist[term->entry]->len + term->out->len);
          memcpy(hist[term->entry]->line + hist[term->entry]->len, term->out->line, term->out->len);
          hist[term->entry]->len += term->out->len;
        }
        if (!term->quo[0]) {
          term->reset = 1;
        }
        else if (term->quo[0]) {
          free(term->out->line);
          free(term->out->tail);
          term->out->tail = NULL;
          term->out->line = NULL;
          term->out->line = (char *)malloc(sizeof(char) * 100);
          term->out->len = 0;
          term->pos = 0;
          term->mo_y = 1;
          term->mo_x++;
          write(1, "\r\n", 2);
          write(1, "blockqoute> ", 12);
        }
      }
      else if (!term->quo[0]) {
        write(1, "\n\r", 2);
        fflush(stdout);
        free(term->out->line);
        free(term->out->tail);
        term->out->tail = NULL;
        term->out->line = NULL;
        term->out->line = (char *)malloc(sizeof(char) * 100);
        term->out->len = 0;
        term->pos = 0;
        term->mo_y = 1;
        term->mo_x++;
        refresh_line(term, 5);
      }
      else {
        term->mo_x++;
        fflush(stdout);
        free(term->out->line);
        free(term->out->tail);
        term->out->tail = NULL;
        term->out->line = NULL;
        term->out->line = (char *)malloc(sizeof(char) * 100);
        term->out->len = 0;
        term->pos = 0;
        term->mo_y = 1;
        write(1, "\r\n", 2);
        write(1, "blockqoute> ", 12);
      }
      break;
    case '\t':
      get_cursor(&term->y, &term->x);
      write(1, "\x1b[J", 3);
      if (term->out->len) {
        char **buf = (char **)malloc(sizeof(char *) * 100);
        int max_len = 0;
        int j = 0;
        for (int i = 0; i < term->count + 9; i++) {
          if (false == strncmp(term->out->line, term->command[i], term->out->len))
            buf[j++] = mx_strdup(term->command[i]);
            if ((int)strlen(term->command[i]) > max_len)
              max_len = strlen(term->command[i]);
        }
        if (j == 1) {
          write(1, "\r", 1);
          refresh_line(term, 5);
          write(1, buf[0], strlen(buf[0]));
          term->mo_y = strlen(buf[0]) + 1;
          free(term->out->line);
          term->out->line = mx_strdup(buf[0]);
          term->out->len = strlen(buf[0]);
        }
        else if (j > 1) {
          term->mo_y = term->out->len + 1;
          write(1, "\n\r", 2);
          for (int i = 0; i < j; i++) {
            write(1, buf[i], strlen(buf[i]));
            // if ((int)strlen(buf[i]) < max_len) {
            // for (int k = 0; k < max_len - (int)strlen(buf[i]); k++)
            //   write(1, " ", 1); 
            // }
            write(1, "\t", 1);
           }
           if (term->mo_x >= term->row)
            term->mo_x = term->x - 1;
            write(1, "\x1b[", 2);
            write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
            write(1, ";", 1);
            write(1, mx_itoa(term->mo_y), strlen(mx_itoa(term->mo_y)));
            write(1, "H", 1);
          }
        }
    break;
    case CTRL_KEY('l'):
      term->mo_x = 1;
      write(1, "\r", 1);
      write(STDOUT_FILENO, "\x1b[2J", 4);
      write(1, "\x1b[", 2);
      write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
      write(1, ";", 1);
      write(1, mx_itoa(term->mo_y), strlen(mx_itoa(term->mo_y)));
      write(1, "H", 1);
      write(1, "u$h> ", strlen("u$h> "));
    break;
    case CTRL_KEY('d'):
        cooked_mode_on();
        tcsetattr(0, TCSAFLUSH, &term->origin);
        write (1, "\n", 1);
        exit(0);
      break;
      case CTRL_KEY('c'):
        write(1, "^C", strlen("^C"));
        cooked_mode_on();
        tcsetattr(0, TCSAFLUSH, &term->origin);
        write (1, "\n\r", 2);
        exit(130);
        break;
      case MX_BACKSPACE:
        if (term->mo_y > 1) {
          if (term->mo_y - 1 < term->out->len) {
            term->pos = term->mo_y - 1;
            term->out->tail = mx_strndup(term->out->line + term->pos, term->out->len - term->pos);
            term->out->line = realloc(term->out->line, term->pos);
            --term->pos;
            --term->mo_y;
            --term->out->len;
            write(STDOUT_FILENO, MX_DELBUF, strlen(MX_DELBUF));
            write(STDOUT_FILENO, "\x1b[0J", 4);
            term->out->line = realloc(term->out->line, term->out->len);
            memcpy(term->out->line + term->pos, term->out->tail, strlen(term->out->tail));
            write(STDOUT_FILENO, term->out->tail, strlen(term->out->tail));
          }
          else {
          term->pos = term->mo_y - 1;
          term->out->line = realloc(term->out->line, term->pos);
          --term->pos;
          --term->out->len;
          --term->mo_y;
          write(STDOUT_FILENO, MX_DELBUF, strlen(MX_DELBUF));
          write(STDOUT_FILENO, "\x1b[0J", 4);
          }
        }
        break;
    case MX_HOME_KEY:
      term->mo_y = 1;
      break;
    case MX_END_KEY:
      term->mo_y = term->out->len + 1;
      break;
    case MX_PAGE_DOWN:
    case MX_PAGE_UP:
      write(1, "~", 1);
      term->mo_y++;
      break;
    case MX_ARROW_DOWN:
    case MX_ARROW_UP:
    case MX_ARROW_RIGHT:
    case MX_ARROW_LEFT:
      arrows_motion(c, term, hist);
      break;
    default:
      editor_processing(term, c);
      break;
  }
}

void loop(config* term, t_hist **hist) {
  raw_mode_on();
  get_cursor(&term->y, &term->x);
  term->mo_x = term->x;
  term->mo_y = term->y;
  refresh_line(term, 5);
  while (1) {
    write(1, "\x1b[?25h", 6);
    processKey(term, hist);
    write(1, "\x1b[?25l", 6);
    get_cursor(&term->y, &term->x);
    term->mo_x = term->x;
    if (!term->quo[0])
      refresh_screen(term, 5);
    else
      refresh_screen(term, 12);
    if (term->reset) {
      term->reset = 0;
      write(1, "\n\r", 2);
      write(STDOUT_FILENO, "\x1b[0J", 4); //this line removes command assumptions
      cooked_mode_on();
      tcsetattr(0, TCSAFLUSH, &term->origin);
      write(1, hist[term->entry]->line, hist[term->entry]->len);
      term->entry++;
      term->total = term->entry;
      fflush(stdout);
      free(term->out->line);
      free(term->out->tail);
      free(term->quo);
      term->out->tail = NULL;
      term->out->line = NULL;
      term->quo = NULL;
      term->quo = (int *)malloc(sizeof(int) * 2);
      term->quo[0] = 0;
      term->quo[1] = 0;
      term->q_id = 0;
      term->out->line = (char *)malloc(sizeof(char) * 100);
      term->out->len = 0;
      term->pos = 0;
      raw_mode_on();
      write(1, "\r\n", 2);
      term->mo_x = term->mo_x + 2;
      refresh_line(term, 5);
    }
  }
  cooked_mode_on();
  tcsetattr(0, TCSAFLUSH, &term->origin);
}

void get_term_params(config *term) {
  char *termtype = getenv("TERM");
  char buf[2048];
  tgetent (buf, termtype);

  term->col = tgetnum("co");
  term->row = tgetnum("li");
}

config *config_init() {
  config *term = (config *)malloc(sizeof(config));
  term->out = (t_row *)malloc(sizeof(t_row));
  term->out->line = (char *)malloc(sizeof(char) * 100);
  term->out->tail = NULL;
  term->count = 0;
  term->entry = 0;
  term->pos = 0;
  term->out->len = 0;
  term->row = 0;
  term->col = 0;
  term->quo = (int *)malloc(sizeof(int) * 2);
  term->quo[0] = 0;
  term->quo[1] = 0;
  term->q_id = 0;
  term->x = 0;
  term->y = 0;
  term->mo_x = 0;
  term->mo_y = 0;
  tcgetattr(0, &term->origin);
  tcgetattr(0, &term->raw);
  return term;
}

static bool comparator(const char *name) {
    bool is_dir = 0;

    if (strcmp(name, ".") == 0)
        is_dir = 1;
    if (strcmp(name, "..") == 0)
        is_dir = 1;
    return is_dir;
}

static int count_processor(DIR *mydir) {
    struct dirent *myfile;
    int count = 0;

    while((myfile = readdir(mydir)) != NULL) {
      if (myfile->d_name[0] != '.' && comparator(myfile->d_name) == 0)
          count++;
    }
    return count;
}

void get_commands(config *term) {
  char *builtins[9] = {"export", "unset", "exit", "fg", "env", "cd", "pwd", "which", "echo"};
  struct dirent *dirptr;
  int i = 0;
  DIR *mydir;

  if ((mydir = opendir("/bin")) != NULL) {
    term->count = count_processor(mydir);
  }
  closedir(mydir);
  term->command = (char **)malloc(sizeof(char *) * (term->count + 9));
  if ((mydir = opendir("/bin")) != NULL) {
        while((dirptr = readdir(mydir)) != NULL) {
          if (dirptr->d_name[0] != '.'
              && comparator(dirptr->d_name) == 0)
              term->command[i++] = mx_strdup(dirptr->d_name);
        }
  }
  closedir(mydir);
  for (int j = 0; j < 9; j++)
    term->command[i++] = mx_strdup(builtins[j]);
}

int main(int argc, char **argv, char **envp) {
  (void)envp;
  (void)argv;
  (void)argc;
  config *term = config_init();
  t_hist **hist = (t_hist **)malloc(sizeof(t_hist) * 100);
  get_term_params(term);
  get_commands(term);
  if (isatty(0)) {
    loop(term, hist);
  }
  return 0;
}
