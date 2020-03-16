#include "libmx.h"

unsigned int mx_findlen(const char *s) {
    unsigned int i = 0;

    if (s) {
        while (s[i] != '\0') {
            i++;
        }
        return i;
    }
    return 0;
}
