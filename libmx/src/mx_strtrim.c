#include "libmx.h"

char *mx_strtrim(const char *str) {
    char *res = NULL;
    int start = 0;
    int end;

    if (str) {
        end = mx_strlen(str) - 1;
        while (mx_is_space(str[start]) != 0)
            start++;
        while (mx_is_space(str[end]) != 0)
            end--;
        res = mx_strnew(end - start + 1);
        for (int i = 0; start <= end; i++, start++)
            res[i] = str[start];
        return res;
    }
    return NULL;
}
