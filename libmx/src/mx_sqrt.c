#include "libmx.h"

int mx_sqrt(int x) {
    int half = 1;

    while (half <= 46340) {
        if (half * half == x)
            return half;
        half++;
    }
    return 0;
}
