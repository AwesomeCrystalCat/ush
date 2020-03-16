#include "libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    int i = 0;
    int j = 0;
    char *str = NULL;

    if (s1 && s2) {
        str = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
        for (; i <= mx_strlen(s1); i++)
            str[i] = s1[i];
        i--;
        for (; j <= mx_strlen(s1) + mx_strlen(s2)
            && i <= mx_strlen(s1) + mx_strlen(s2); j++, i++)
            str[i] = s2[j];
    }
    else if (s1)
        return mx_strdup(s1);
    else if (s2)
        return mx_strdup(s2);
    return str;
}
