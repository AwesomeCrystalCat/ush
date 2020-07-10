#include "ush.h"

void mx_set_cursor(t_config *term) {
    if (term->num > 1 && term->x + term->x_offset >= term->row)
        term->mo_x = term->row - term->x_offset;
    write(1, "\x1b[", 2);
    write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
    write(1, ";", 1);
    write(1, mx_itoa(term->mo_y), strlen(mx_itoa(term->mo_y)));
    write(1, "H", 1);
}
