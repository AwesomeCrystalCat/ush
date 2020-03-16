#include "libmx.h"

void *mx_memcpy(void *restrict dst,
const void *restrict src, size_t n) {
    char *src1 = NULL;
    char *dst1 = NULL;

    if (src && dst) {
        src1 = (char *) src;
        dst1 = (char *) dst;
        for (size_t i = 0; i < n; i++)
            dst1[i] = src1[i];
    }
    return dst1;
}
