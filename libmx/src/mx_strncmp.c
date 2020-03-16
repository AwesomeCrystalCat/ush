#include "libmx.h"

int mx_strncmp(const char *s1, const char *s2) {
    int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i++;
    if (i < mx_strlen(s2))
        return 0;
    return 1;
}
