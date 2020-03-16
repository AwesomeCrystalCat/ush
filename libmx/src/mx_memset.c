#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    char *ptr = NULL;

    if (b) {
        ptr = (char *) b;
        for (unsigned int i = 0; i < len; i++)
            ptr[i] = c;
    }
    return ptr;
}
