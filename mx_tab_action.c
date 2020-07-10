#include "ush.h"

static void single_assumption(t_config *term, char *str) {
    write(1, "\r", 1);
    write(1, "\x1b[0J", 4);
    mx_refresh_line(term, 5);
    write(1, str, strlen(str));
    term->mo_y = strlen(str) + 1;
    free(term->out->line);
    term->out->line = mx_strdup(str);
    term->out->len = strlen(str);
}

static void print_assumptions(t_config *term, int total_len) {
    write(1, "\n\r", 2);
    for (int i = 0; i < term->num;) {
        total_len += term->max_len + 8;
        if (total_len <= term->col) {
            write(1, term->buf[i], strlen(term->buf[i]));
            if ((int)strlen(term->buf[i]) < term->max_len) {
                for (int k = 0;
                     k <= term->max_len - (int)strlen(term->buf[i]); k++)
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

static void multi_assumption(t_config *term) {
    int total_len = 0;

    if (term->press == 0 && term->num > 1)
        term->mo_y = term->out->len + 1;
    else if (term->press == 0 && term-> num == 1) {
        single_assumption(term, term->buf[0]);
        term->press = 0;
        term->num = 0;
    }
    if (term->num > 1) {
        if (term->press > 0)
            single_assumption(term, term->buf[term->press - 1]);
    }
    print_assumptions(term, total_len);
    term->press++;
    if (term->press > term->num)
        term->press = 1;
}

static void print_tail(t_config *term) {
    if (term->out->tail) {
        write(1, term->out->tail, strlen(term->out->tail));
        term->mo_y = term->out->len + 1;
        write(1, "\x1b[J", 3);
    }
}

void mx_tab_action(t_config *term) {
    print_tail(term);
    if (term->out->len) {
        term->x_offset = 1;
        write(1, "\x1b[J", 3);
        mx_get_cursor(&term->y, &term->x);
        if (term->press == 0) {
            for (int i = 0; i < term->count; i++) {
                if (!strncmp(term->out->line,
                    term->command[i], term->out->len))
                    term->buf[term->num++] = mx_strdup(term->command[i]);
                if ((int)strlen(term->command[i]) > term->max_len)
                    term->max_len = strlen(term->command[i]);
            }
        }
        if (term->num > 0)
            multi_assumption(term);
        mx_set_cursor(term);
    }
}
