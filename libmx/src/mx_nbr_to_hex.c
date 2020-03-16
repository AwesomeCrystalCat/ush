#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    unsigned long dec = 0;
    unsigned long nbr1 = nbr;
    int i = 0;
    char *hex = NULL;

    while (nbr > 0) {
        nbr = nbr / 16;
        i++;
    }
    hex = mx_strnew(i);
    while (nbr1 != 0) {
        i--;
        dec = nbr1 % 16;
        if (dec <= 9)
            hex[i] = dec + 48;
        if (dec > 9)
            hex[i] = dec + 87;
        nbr1 = nbr1 / 16;
    }
    return hex;
}
