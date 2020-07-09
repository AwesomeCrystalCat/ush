#include "ush.h"

void mx_refresh_line(t_config* term, int offset) {
    term->mo_y = 1;
    write(1, "\r", 1);
    write(1, "u$h> ", strlen("u$h> "));
    write(1, "\x1b[", 2);
    write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
    write(1, ";", 1);
    write(1, mx_itoa(term->mo_y + offset),
          strlen(mx_itoa(term->mo_y + offset)));
    write(1, "H", 1);
}
