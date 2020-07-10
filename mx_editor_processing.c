#include "ush.h"

static void position_conditions(t_config* term) {
    if (term->mo_y - 1 < term->pos) {
        term->out->tail = mx_strndup(term->out->line + term->mo_y - 1,
                                     term->out->len - term->mo_y + 1);
        term->pos = term->mo_y - 1;
    }
    else if (term->mo_y - 1 == term->out->len) {
        term->pos = term->mo_y - 1;
        if (term->out->tail != NULL) {
            free(term->out->tail);
            term->out->tail = NULL;
        }
        term->out->line = realloc(term->out->line, term->out->len + 1);
    }
    else if (term->mo_y - 1 > term->pos && term->mo_y - 1 < term->out->len) {
        term->out->tail = mx_strndup(term->out->line + term->mo_y - 1,
                                     term->out->len - term->mo_y + 1);
        term->pos = term->mo_y - 1;
    }
}

void mx_editor_processing(t_config* term, int c) {
    mx_free_assumptions(term);
    if (term->out->line == NULL) {
        term->out->line = (char *)malloc(sizeof(char) * 100);
    }
    position_conditions(term);
    term->out->len++;
    term->out->line[term->pos++] = c;
    term->mo_y++;
    write(STDIN_FILENO, &c, 1);
    if (term->out->tail != NULL) {
        term->out->line = realloc(term->out->line, term->out->len);
        memcpy(term->out->line + term->pos,
               term->out->tail, strlen(term->out->tail));
        write(STDIN_FILENO, term->out->tail, strlen(term->out->tail));
    }
}
