#include "libmx.h"

static int count_len(int number) {
    int len = 1;

    if (number < 0) {
        if (number == -2147483648) {
            number = -147483648;
            len = 2;
        }
        number = -number;
    }
    else if (number > 0)
        len = 0;
    while (number > 0) {
        len++;
        number /= 10;
    }
    return len;
}

char *mx_itoa(int number) {
    char *str = NULL;
    int len = count_len(number);

    str = mx_strnew(len);
    if (number == 0)
        str[0] = '0';
    if (number < 0) {
        str[0] = '-';
        if (number == -2147483648) {
            str[1] = '2';
            number = -147483648;
        }
        number = -number;
    }
    for (; number > 0; number /= 10) {
        len--;
        str[len] = (number % 10) + 48;
    }
    return str;
}
