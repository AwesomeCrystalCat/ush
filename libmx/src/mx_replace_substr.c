#include "libmx.h"

static char *replacer(char *res, const char *str,
const char *sub, const char *replace) {
    int i = 0;
    int j = 0;

    while (i < mx_strlen(str)) {
        if (mx_strncmp(&str[i], sub) == 1) {
            mx_strncpy(&res[j], replace, mx_strlen(replace));
            i += mx_strlen(sub);
            j += mx_strlen(replace);
        }
        else {
            res[j] = str[i];
            i++;
            j++;
        }
    }
    return res;
}

char *mx_replace_substr(const char *str,
const char *sub, const char *replace) {
    char *res = NULL;
    int new_s;
    int sub_s;
    int rep_s;
    int sub_n;

    if (str != NULL && sub != NULL && replace != NULL) {
        new_s = 0;
        sub_s = mx_strlen(sub);
        rep_s = mx_strlen(replace);
        sub_n = mx_count_substr(str, sub);
        if (sub_s == 0)
            return (char *)str;
        new_s = mx_strlen(str) - (sub_n * sub_s) + (sub_n * rep_s);
        res = mx_strnew(new_s);
        res = replacer(res, str, sub, replace);
    }
    return res;
}
