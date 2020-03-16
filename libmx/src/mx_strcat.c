#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int len1;
    int len2;
    int i;
    int j;
    char *str = NULL;

    if (s1 && s2) {
        len1 = mx_strlen(s1);
        len2 = mx_strlen(s2);
        i = 0;
        j = 0;
        str = mx_strnew(len1 + len2);
        for(; i <= len1; i++)
            str[i] = s1[i];
        i--;
        for(; j <= len1 + len2 && i <= len1 + len2; j++, i++)
            str[i] = s2[j];
        return str;
    }
    return 0;
}
