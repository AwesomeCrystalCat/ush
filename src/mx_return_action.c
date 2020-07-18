#include "ush.h"

static void history_entries(t_config *term) {
    if (term->str == NULL) {
        term->str = mx_strndup(term->out->line, term->out->len);
        term->str_len = term->out->len;
    }
    else {
        term->str = realloc(term->str, term->str_len + term->out->len);
        memcpy(term->str + term->str_len, term->out->line, term->out->len);
        term->str_len = term->str_len + term->out->len;
    }
}

static void clean_up(t_config *term) {
    fflush(stdout);
    free(term->out->line);
    free(term->out->tail);
    term->out->tail = NULL;
    term->out->line = NULL;
    term->out->len = 0;
    term->pos = 0;
    term->mo_y = 1;
    term->mo_x++;
}

static void quotes_result(t_config *term) {
    clean_up(term);
    if (term->quo[0] == 96 || term->quo[1] == 96)
        write(1, "\r\nbqoute> ", 10);
    else if (term->quo[0] == 34 && term->quo[1] != 96)
        write(1, "\r\ndqoute> ", 10);
    else if (term->quo[0] == 39 && term->quo[1] != 96)
        write(1, "\r\nqoute> ", 9);
}

void mx_return_action(t_config *term) {
    if (term->out->len > 0) {
        mx_qoutes_handling(term);
        history_entries(term);
        if (!term->quo[0])
            term->reset = 1;
        else
            quotes_result(term);
    }
    else if (!term->quo[0]) {
        write(1, "\n\r", 2);
        clean_up(term);
        mx_refresh_line(term, 5);
    }
    else
        quotes_result(term);
}
