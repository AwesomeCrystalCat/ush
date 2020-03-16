#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long res = 0;
    unsigned long pow = 1;
    int i = 0;

    if (hex) {
        for (; hex[i + 1] != '\0'; i++);
        while (i >= 0) {
            if (hex[i] >= '0' && hex[i] <= '9')
                res = (hex[i] - '0') * pow + res;
            else if (hex[i] >= 'A' && hex[i] <= 'F')
                res = (hex[i] - 'A' + 10) * pow + res;
            else if (hex[i] >= 'a' && hex[i] <= 'f')
                res = (hex[i] - 'a' + 10) * pow + res;
            else
                return 0;
            pow *= 16;
            --i;
        }
    }
    return res;
}
