#include "ush.h"

static const char *make_name(void) {
    char name[4096];
    int len = 0;
    int i = 0;
    const char *buff = NULL;

    if (getcwd(name, sizeof(name)) != NULL) {
        len = strlen(name);
        i = len;
        for (; i != 0; i--) {
            if (name[i] == '/')
            break;
        }
        buff = mx_strndup(&name[i + 1], len - i - 1);
        return buff;
    }
    return NULL;
}

static void plane_print(t_config* term, int offset, int len) {
    write(1, "u$h> ", strlen("u$h> "));
    write(1, "\x1b[", 2);
    write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
    write(1, ";", 1);
    write(1, mx_itoa(term->mo_y + offset + len),
          strlen(mx_itoa(term->mo_y + offset + len)));
    write(1, "H", 1);
}

void mx_refresh_line(t_config* term, int offset) {
    const char *str = make_name();
    int len = 0;  

    term->mo_y = 1;
    write(1, "\r", 1);
    if (str != NULL) {
        len = strlen(str) + 3;
        write(1, "\x1b[1m\x1b[34m", strlen("\x1b[1m\x1b[34m"));
        write(1, "~/", 2);
        write(1, str, strlen(str));
        write(1, "\x1b[0m", strlen("\x1b[0m"));
        write(1, " ", 1);
        free((void *)str);
    }
    plane_print(term, offset, len);
}
