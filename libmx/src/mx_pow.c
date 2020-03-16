#include "libmx.h"

double mx_pow(double n, unsigned int pow) {
    double r;

    r = n;
    if (n == 0)
        return 0;
    if (pow == 0 || n == -1 || n == 1)
        return 1;
    if (pow == 1)
        return r;
    for (unsigned int i = 1; pow > i; i++)
        r = r * n;
    return r;
}
