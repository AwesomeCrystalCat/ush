#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    char *str = NULL;
    unsigned int i = 0;

    if (s) {
        str = (char *) s;
        while (i < n) {
            if (*str == c)
                return str;
            str = str + 1;
            i++;
        }
    }
    return NULL;
}
