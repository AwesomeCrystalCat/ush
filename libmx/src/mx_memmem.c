#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len,
const void *little, size_t little_len) {
    char *haystack = NULL;
    char *needle = NULL;
    unsigned int i = 0;

    if (big && little) { 
        haystack = (char *) big;
        needle = (char *) little;
        while (i < big_len) {
            if (mx_memcmp(needle, haystack, little_len) == 0
                && big_len >= little_len
                && little_len <= mx_findlen(needle))
                return haystack;
            haystack = haystack + 1;
            i++;
        }
    }
    return NULL;
}
