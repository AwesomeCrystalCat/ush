#include "ush.h"

static const char *make_name(void) {
    const char *name = getenv("PWD");
    int len = strlen(name);
    int i = len;
    const char *buff = NULL;

    for (; i != 0; i--) {
        if (name[i] == '/')
            break;
    }
    buff = mx_strndup(&name[i + 1], len - i - 1);
    return buff;
}

void mx_refresh_screen(t_config* term, int offset) {
    if (offset != 12) {
        const char *str = make_name();
        int len = strlen(str);

        write(1, "\x1b[", 2);
        write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
        write(1, ";", 1);
        write(1, mx_itoa(term->mo_y + offset + len + 3),
              strlen(mx_itoa(term->mo_y + offset + len + 3)));
        write(1, "H", 1);
        free((void *)str);
    }
    else {
        write(1, "\x1b[", 2);
        write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
        write(1, ";", 1);
        write(1, mx_itoa(term->mo_y + offset),
              strlen(mx_itoa(term->mo_y + offset)));
        write(1, "H", 1);
    }
}
