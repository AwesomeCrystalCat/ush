#include "ush.h"

static void del_action(t_config *term) {
    --term->pos;
    --term->mo_y;
    --term->out->len;
    write(STDOUT_FILENO, MX_DELBUF, strlen(MX_DELBUF));
    write(STDOUT_FILENO, "\x1b[0J", 4);
}

void mx_backspace_action(t_config *term) {
    if (term->mo_y > 1) {
        mx_free_assumptions(term);
        if (term->mo_y - 1 < term->out->len) {
            term->pos = term->mo_y - 1;
            term->out->tail = mx_strndup(term->out->line + term->pos,
                                         term->out->len - term->pos);
            term->out->line = realloc(term->out->line, term->pos);
            del_action(term);
            term->out->line = realloc(term->out->line, term->out->len);
            memcpy(term->out->line + term->pos,
                   term->out->tail, strlen(term->out->tail));
            write(STDOUT_FILENO, term->out->tail, strlen(term->out->tail));
        }
        else {
            term->pos = term->mo_y - 1;
            term->out->line = realloc(term->out->line, term->pos);
            del_action(term);
        }
    }
}
