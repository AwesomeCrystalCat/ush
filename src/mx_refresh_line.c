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

void mx_refresh_line(t_config* term, int offset) {
    const char *str = make_name();    

    term->mo_y = 1;
    write(1, "\r", 1);
    write(1, "\x1b[1m\x1b[34m", strlen("\x1b[1m\x1b[34m"));
    write(1, "~/", 2);
    write(1, str, strlen(str));
    write(1, "\x1b[0m", strlen("\x1b[35m"));
    write(1, " ", 1);
    write(1, "u$h> ", strlen("u$h> "));
    write(1, "\x1b[", 2);
    write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
    write(1, ";", 1);
    write(1, mx_itoa(term->mo_y + offset + strlen(str) + 3),
          strlen(mx_itoa(term->mo_y + offset + strlen(str) + 3)));
    write(1, "H", 1);
    free((void *)str);
}
