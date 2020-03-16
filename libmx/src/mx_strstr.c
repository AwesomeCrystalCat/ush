#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    char *tail = NULL;
    int len;

    if (haystack && needle) {
        len = mx_strlen(haystack);
        tail = (char *)&haystack[0];
        for (int i = 0; i < len; i++) {
            if (mx_strncmp(tail, needle) == 1)
                return tail;
            tail++;
        }
    }
    return 0;
}
