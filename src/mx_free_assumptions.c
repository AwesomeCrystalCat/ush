#include "ush.h"

void mx_free_assumptions(t_config *term) {
    term->num = 0;
    term->press = 0;
    if (term->buf) {
        if (term->buf[0]) {
            for (int i = 0; i < term->num; i++)
                free(term->buf[i]);
        }
        free(term->buf);
        term->buf = NULL;
        term->buf = (char **)malloc(sizeof(char *) * 300);
    }
}
