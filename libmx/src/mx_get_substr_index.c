#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    char *tail = NULL;
    int len;
    int count;

    if (str && sub && mx_strlen(sub) > 0) {
        tail = (char *)&str[0];
        len = mx_strlen(str);
        count = 0;
        for (; count < len; count++) {
            if (mx_strncmp(tail, sub) == 1)
                return count;
                tail++;
            }
        return -1;
    }
    return -2;
}
