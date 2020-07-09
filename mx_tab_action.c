#include "ush.h"

static void single_assumption(t_config *term, char *str) {
    write(1, "\r", 1);
    mx_refresh_line(term, 5);
    write(1, str, strlen(str));
    term->mo_y = strlen(str) + 1;
    free(term->out->line);
    term->out->line = mx_strdup(str);
    term->out->len = strlen(str);
}

static void multi_assumption(t_config *term, char **buf, int j, int len) {
    int total_len = 0;

    term->mo_y = term->out->len + 1;
    write(1, "\n\r", 2);
    for (int i = 0; i < j;) {
        total_len += len + 8;
        if (total_len <= term->col) {
            write(1, buf[i], strlen(buf[i]));
            if ((int)strlen(buf[i]) < len) {
                for (int k = 0; k <= len - (int)strlen(buf[i]); k++)
                    write(1, " ", 1);
            }
            write(1, "\t", 1);
            i++;
        }
        else {
            term->x_offset++;
            write(1, "\n\r", 2);
            total_len = 0;
        }
    }
}

static void grab_cursor(t_config *term, char **buf, int j) {
    write(1, "\x1b[", 2);
    write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
    write(1, ";", 1);
    write(1, mx_itoa(term->mo_y), strlen(mx_itoa(term->mo_y)));
    write(1, "H", 1);
    if (buf) {
        for (int i = 0; i < j; i++)
            free(buf[j]);
        free(buf);
    }
}

static void tab_count(t_config *term) {
    char **buf = (char **)malloc(sizeof(char *) * 1024);
    int max_len = 0;
    int j = 0;

    for (int i = 0; i < term->count; i++) {
        if (!strncmp(term->out->line, term->command[i], term->out->len))
            buf[j++] = mx_strdup(term->command[i]);
        if ((int)strlen(term->command[i]) > max_len)
            max_len = strlen(term->command[i]);
    }
    if (j == 1)
        single_assumption(term, buf[0]);
    else if (j > 1)
        multi_assumption(term, buf, j, max_len);
    if (term->mo_x >= term->row)
        term->mo_x = term->x - term->x_offset;
    grab_cursor(term, buf, j);
}

void mx_tab_action(t_config *term) {
    term->x_offset = 1;

    mx_get_cursor(&term->y, &term->x);
    write(1, "\x1b[J", 3);
    if (term->out->len)
        tab_count(term);        
}
