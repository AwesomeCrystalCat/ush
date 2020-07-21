#include "ush.h"

static void qoutes_manipulation(t_config *term, int i, int slaash) {
    if (!term->quo[0] && term->out->line[i] == 34
        && term->out->line[i - 1] != 92 && !(slaash % 2))
        term->quo[term->q_id++] = term->out->line[i];
    else if (!term->quo[0] && term->out->line[i] == 39)
        term->quo[term->q_id++] = term->out->line[i];
    else if (term->out->line[i] == 96 && !(slaash % 2) 
             && term->out->line[i - 1] != 92)
        term->quo[term->q_id++] = term->out->line[i];
    else if (term->quo[0] == 39 && term->out->line[i] == 39) {
        term->quo[0] = 0;
        term->q_id--;
    }
    else if (term->quo[0] == term->out->line[i]
             && term->out->line[i - 1] != 92) {
        term->quo[0] = 0;
        term->q_id--;
    }
}

void mx_qoutes_handling(t_config *term) {
    int slaash = 0;

    for (int i = 0; i < term->out->len; i++) {
        if (term->out->line[i] == 92)
            slaash++;
        if (term->quo[0] != 96 && term->quo[1] != 96)
            qoutes_manipulation(term, i, slaash);
        else if (term->quo[0] == 96
                 && term->quo[0] == term->out->line[i]
                 && term->out->line[i - 1] != 92) {
            term->quo[0] = 0;
            term->q_id--;
        }
        else if (term->quo[1] == term->out->line[i]
                 && term->out->line[i - 1] != 92) {
            term->quo[1] = 0;
            term->q_id--;
        }
    }
}
