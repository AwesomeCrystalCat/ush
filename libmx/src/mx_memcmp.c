#include "libmx.h" 

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    unsigned int i = 0;
    char *str1 = NULL;
    char *str2 = NULL;

    str1 = (char *) s1;
    str2 = (char *) s2;
    while ((str1[i] == str2[i]) && (i < n)) {
        i++;
        if (i == n)
            return 0;
    }
    return str1[i] - str2[i];
}
