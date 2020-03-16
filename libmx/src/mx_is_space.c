#include "libmx.h"

bool mx_is_space(char c) {
    if ((c >= 8 && c <= 13) || (c == 32))
        return 1;
    else
        return 0;
}
