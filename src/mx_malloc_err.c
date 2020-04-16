#include "ush.h"

void mx_malloc_err() {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
}
