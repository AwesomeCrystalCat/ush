#include "libmx.h"

int mx_count_words(const char *str, char c) {
    int count = -1;
    int len;

    if (str) {
        len = mx_strlen(str);
        count = 0;
        for (int i = 0; i < len; i++) {
            while (str[i] == c)
                i++;
            if (str[i] != c && i < len) {
                while (str[i] != c && i < len)
                    i++;
                count++;
            }
        }
    }
    return count;
}
