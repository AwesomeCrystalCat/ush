#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src,
int c, size_t n) {
    char *d = NULL;
    char *s = NULL;

    if (dst && src && n) {
        d = (char *)dst;
        s = (char *)src;
        for (size_t i = 0; i < n; ++i) {
            d[i] = s[i];
            if (s[i] == c)
                return (void *)(d + i + 1);
        }
    }
    return NULL;
}
