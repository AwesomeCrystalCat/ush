#include "ush.h"

static void clean_up(t_config* term) {
    fflush(stdout);
    mx_free_assumptions(term);
    free(term->out->line);
    free(term->out->tail);
    free(term->quo);
    free(term->str);
    term->str = NULL;
    term->out->tail = NULL;
    term->out->line = NULL;
    term->quo = NULL;
    term->quo = (int *)malloc(sizeof(int) * 2);
    term->quo[0] = 0;
    term->quo[1] = 0;
    term->q_id = 0;
    term->out->len = 0;
    term->pos = 0;
    term->total = 0;
    term->entry = 0;
}

static void write_hist(int len, char *str) {
    char *tmp = mx_strndup(str, len);
    FILE * fp;

    fp = fopen (".file.txt", "a");
    fprintf(fp, "%s\t", tmp);
    fclose(fp);
    free(tmp);
}

static void lets_cat(char **envp) {
    char* args[] = { "/bin/cat", NULL };
    execve("/bin/cat", args, envp);
    // Unreachable
}

static void process_create(char **envp) {
  pid_t pid;
//   int rv = 1;
  switch(pid=fork()) {
  case -1:
          perror("fork"); /* произошла ошибка */
          exit(1); /*выход из родительского процесса*/
  case 0:
          printf(" CHILD: Это процесс-потомок!\n");
          printf(" CHILD: Мой PID -- %d\n", getpid());
          printf(" CHILD: PID моего родителя -- %d\n", getppid());
          printf(" CHILD: Введите мой код возврата (как можно меньше):");
          lets_cat(envp);
          printf(" CHILD: Выход!\n");
        //   exit(rv);
  default:
          printf("PARENT: Это процесс-родитель!\n");
          printf("PARENT: Мой PID -- %d\n", getpid());
          printf("PARENT: PID моего потомка %d\n",pid);
          printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");
          wait(0);
        //   printf("PARENT: Код возврата потомка:%d\n", WEXITSTATUS(rv));
          printf("PARENT: Выход!\n");
    }
}

// static void sighandler(int signum) {
//     (void)signum;
// }

// static void mx_clear() {
//     mx_raw_mode_on();
//     write(1, "\r", 1);
//     write(1, "\x1b[2J", 4); 
//     write(1, "\x1b[1;1H", 6);
// }

// static void mx_history() {
//     char tmp[1024];
//     FILE *fp;

//     if ((fp = fopen (".file.txt", "r"))) {
//         fgets(tmp, 1024, (FILE*)fp);
//         fclose(fp);
//     }
//     if (strlen(tmp)) {
//         char *token = strtok(tmp, "\t");

//         for (int i = 0; token != NULL; i++) {
//             write(1, mx_itoa(i + 1), strlen(mx_itoa(i + 1)));
//         if (i < 10)
//             write(1, " ", 1);
//         if (i < 100)
//             write(1, " ", 1);
//         write(1, token, strlen(token));
//         write(1, "\n", 1);
//         token = strtok(NULL, "\t");
//     }
//     free(token);
//     }
// }

static void reset(t_config* term, t_hist **hist, char **envp) {
    write_hist(term->str_len, term->str);
    term->reset = 0;
    write(1, "\n\r\x1b[0J", 6);
    mx_cooked_mode_on();
    tcsetattr(0, TCSAFLUSH, &term->origin);
    write(1, term->str, term->str_len);
    signal(SIGINT, mx_sighandler);
    signal(SIGQUIT, mx_sighandler);
    if (!strcmp("exit", term->str))
        exit(0);
    else if (!strcmp("clear", term->str))
        mx_clear();
    else if (!strcmp("history", term->str))
        mx_history();
    else if (!strcmp("help", term->str))
        mx_help();
    else
        process_create(envp);    
    if (hist[0]->line != NULL) {
        for (int i = 0; i < term->entry; i++) {
            free(hist[i]->line);
            hist[i]->line = NULL;
            hist[i]->len = 0;
        }
    }
    clean_up(term);
    mx_raw_mode_on();
    write(1, "\r\n", 2);
    mx_get_cursor(&term->y, &term->x);
    term->mo_x = term->x;
    mx_refresh_line(term, 5);
}

static void inner_loop(t_config* term, t_hist **hist, char **envp) {
    mx_get_term_params(term);
    write(1, "\x1b[?25h", 6);
    mx_process_key(term, hist);
    write(1, "\x1b[?25l", 6);
    mx_get_cursor(&term->y, &term->x);
    term->mo_x = term->x;
    if (!term->quo[0])
        mx_refresh_screen(term, 5);
    else if (term->quo[0] == 39 && term->quo[1] != 96)
        mx_refresh_screen(term, 0);
    else
        mx_refresh_screen(term, 1);
    if (term->reset)
        reset(term, hist, envp);
}

void mx_loop(t_config* term, t_hist **hist, char **envp) {
    mx_get_commands(term);
    mx_get_term_params(term);
    mx_raw_mode_on();
    mx_get_cursor(&term->y, &term->x);
    term->mo_x = term->x;
    term->mo_y = term->y;
    mx_refresh_line(term, 5);
    while (1)
        inner_loop(term, hist, envp);
    mx_cooked_mode_on();
    tcsetattr(0, TCSAFLUSH, &term->origin);
}
