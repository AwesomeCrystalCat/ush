#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    char *tmp = NULL;
    char *res = NULL;
    int j = 0;

    if (str) {
        tmp = mx_strtrim(str);
        res = mx_strnew(mx_count_chars(tmp));
        for (int i = 0; tmp[i] != '\0';) {
            for (; tmp[i] != '\0' && mx_is_space(tmp[i]) == 1; i++);
            while (tmp[i] != '\0' && mx_is_space(tmp[i]) == 0) {
                res[j++] = tmp[i++];
                if (j <= mx_count_chars(tmp)
                    && mx_is_space(tmp[i]) == 1)
                    res[j++] = 32;
            }
        }
    }
    free(tmp);
    return res;
}
