#include "ush.h"

void mx_refresh_screen(t_config* term, int offset) {
    write(1, "\x1b[", 2);
    write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
    write(1, ";", 1);
    write(1, mx_itoa(term->mo_y + offset),
          strlen(mx_itoa(term->mo_y + offset)));
    write(1, "H", 1);
}
