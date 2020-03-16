#include "libmx.h"

void mx_printstr(const char *s) {
    int i;

    if (s) {
        i = 0;
        while(s[i] != '\0') {
            mx_printchar(s[i]);
            i++;
        }
    }
}
