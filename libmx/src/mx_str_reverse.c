#include "libmx.h"

void mx_str_reverse(char *s) {
    char *start;
    char *end;
    int len;

    if (s) {
        len = mx_strlen(s);
        start = &s[0];
        end = &s[len - 1];
        for (int i = 0; i < len / 2; i++) {
            mx_swap_char(start, end);
            start++;
            end--;
        }
    }
}
