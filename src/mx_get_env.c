#include "ush.h"

char *mx_get_env(char *c, int k) {
    char *res = NULL;
    int first = k;
    int n = 0;

    if (c[k] >= '0' && c[k] <= '9') {
        for (; c[k] >= '0' && c[k] <= '9'; k++)
            n++;
    }
    else if ((c[k] >= 'a' && c[k] <= 'z')
        || (c[k] >= 'A' && c[k] <= 'Z')) {
        for (; (c[k] >= '0' && c[k] <= '9')
            || (c[k] >= 'a' && c[k] <= 'z')
            || (c[k] >= 'A' && c[k] <= 'Z'); k++)
            n++;
    }
    res = mx_strndup(&c[first], n);
    return res;
}
