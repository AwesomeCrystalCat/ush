#include "ush.h"

void mx_get_cursor(int *y, int *x) {
    char buf[30];
    int i;
    char ch;

    write(1, "\033[6n", 4);
    for (i = 0, ch = 0; ch != 'R'; i++ ) {
        read(0, &ch, 1);
        buf[i] = ch;
    }
    sscanf(&buf[2], "%d;%d", x, y);
}
