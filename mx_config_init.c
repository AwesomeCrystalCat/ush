#include "ush.h"

static void qoutes_init(t_config *term) {
    term->total = 0;
    term->num = 0;
    term->press = 0;
    term->buf = NULL;
    term->buf = (char **)malloc(sizeof(char *) * 300);
    term->quo = NULL; 
    term->quo = (int *)malloc(sizeof(int) * 2);
    term->quo[0] = 0;
    term->quo[1] = 0;
    term->q_id = 0;
}

t_config *mx_config_init(void) {
    t_config *term = (t_config *)malloc(sizeof(t_config));

    term->out = (t_row *)malloc(sizeof(t_row));
    term->out->line = NULL;
    term->out->tail = NULL;
    term->str = NULL;
    term->count = 0;
    term->entry = 0;
    term->pos = 0;
    term->out->len = 0;
    qoutes_init(term);
    term->row = 0;
    term->col = 0;
    term->x = 0;
    term->y = 0;
    term->mo_x = 0;
    term->mo_y = 0;
    tcgetattr(0, &term->origin);
    tcgetattr(0, &term->raw);
    return term;
}
