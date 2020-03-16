#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    char *tail = NULL;
    int count = 0;

    if (str && sub) {
        tail = (char *)&str[0];
        if (tail[0] == '\0' || sub[0] == '\0')
            return 0;
        while (mx_strlen(tail) > 0) {
            if (mx_strncmp(tail, sub) == 1) {
                count++;
                tail = tail + mx_strlen(sub);
            }
            else
                tail++;
        }
        return count;
    }
    return -1;
}
