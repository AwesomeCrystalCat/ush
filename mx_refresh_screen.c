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

static void plane_print(t_config* term, int offset) {
    write(1, "\x1b[", 2);
    write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
    write(1, ";", 1);
    write(1, mx_itoa(term->mo_y + offset),
          strlen(mx_itoa(term->mo_y + offset)));
    write(1, "H", 1);
}

void mx_refresh_screen(t_config* term, int offset) {
    const char *str = make_name();
    int len = 0;

    if (offset != 12 && str != NULL) {
        len = strlen(str) + 3;
        write(1, "\x1b[", 2);
        write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
        write(1, ";", 1);
        write(1, mx_itoa(term->mo_y + offset + len),
              strlen(mx_itoa(term->mo_y + offset + len)));
        write(1, "H", 1);
        free((void *)str);
    }
    else
       plane_print(term, offset);
}
