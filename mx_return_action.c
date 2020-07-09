#include "ush.h"

static void history_entries(t_config *term, t_hist **hist) {
    if (!hist[term->entry]) {
        hist[term->entry] = (t_hist *)malloc(sizeof(t_hist) * 1);
        hist[term->entry]->id = term->entry;
        hist[term->entry]->len = term->out->len;
        hist[term->entry]->line = mx_strndup(term->out->line,
                                             term->out->len);
    }
    else {
        hist[term->entry]->line = realloc(hist[term->entry]->line,
                                          hist[term->entry]->len
                                          + term->out->len);
        memcpy(hist[term->entry]->line + hist[term->entry]->len,
               term->out->line, term->out->len);
        hist[term->entry]->len += term->out->len;
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

static void blckqt_act(t_config *term) {
    clean_up(term);
    write(1, "\r\nblockqoute> ", 14);
}

void mx_return_action(t_config *term, t_hist **hist) {
    if (term->out->len > 0) {
        mx_qoutes_handling(term);
        history_entries(term, hist);
        if (!term->quo[0])
            term->reset = 1;
        else if (term->quo[0])
            blckqt_act(term);
    }
    else if (!term->quo[0]) {
        write(1, "\n\r", 2);
        clean_up(term);
        mx_refresh_line(term, 5);
    }
    else
        blckqt_act(term);
}
