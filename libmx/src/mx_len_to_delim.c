#include "libmx.h"

int mx_len_to_delim(char *str, char c) {
    int i = 0;
    if(!str) return 0;
    for (; str[i] != '\0' && str[i] != c; i++)
    ;
    return i;
}



