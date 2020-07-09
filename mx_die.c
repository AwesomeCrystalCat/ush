#include "ush.h"

void mx_die(const char *str) {
    perror(str);
    exit(1);
}
