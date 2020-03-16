#include "libmx.h"

int mx_count_chars(const char *str) {
    int res_len = 0;
    int len = 0;

    if (str) {
        len = mx_strlen(str);
        for (int i = 0; i < len; i++) {
            if (mx_is_space(str[i]) == 1) {
                while (mx_is_space(str[i]) == 1)
                    i++;
            }
            while (mx_is_space(str[i]) == 0 && str[i] != '\0') {
                i++;
                res_len++;
            }
            if (str[i] != '\0')
                res_len++;
        }
    }
    return res_len;
}
