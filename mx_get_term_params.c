#include "ush.h"

void mx_get_term_params(t_config *term) {
    char *termtype = getenv("TERM");
    char buf[2048];

    tgetent(buf, termtype);
    term->col = tgetnum("co");
    term->row = tgetnum("li");
}
