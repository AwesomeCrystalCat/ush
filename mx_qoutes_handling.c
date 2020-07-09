#include "ush.h"

void mx_qoutes_handling(t_config *term) {
    for (int i = 0; i < term->out->len; i++)
        if (term->quo[0] != 96 && term->quo[1] != 96) {
            if (!term->quo[0] && (term->out->line[i] == 34
                || term->out->line[i] == 39))
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
