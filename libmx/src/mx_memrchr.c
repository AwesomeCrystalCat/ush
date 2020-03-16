#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    char *str = NULL;
    int len;

    if (s) {
        str = (char *) s;
        len = mx_strlen(str) - 1;
        while (len >= 0 && n != 0) {
            if (str[len] == c)
                return &str[len];
            n--;
            len--;
        }
        return NULL;
    }
    return NULL;
}
