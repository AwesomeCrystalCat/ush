#include "ush.h"

void mx_clear_screen(t_config* term) {
    if (term->out->line) {
        free(term->out->line);
        term->out->line = NULL;
        term->out->len = 0;
    }
    term->mo_x = 1;
    write(1, "\r", 1);
    write(1, "\x1b[2J", 4); 
    write(1, "\x1b[", 2);
    write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
    write(1, ";", 1);
    write(1, mx_itoa(term->mo_y), strlen(mx_itoa(term->mo_y)));
    write(1, "H", 1);
    mx_refresh_line(term, 5);
}
