#include "ush.h"

void mx_clear(void) {
    mx_raw_mode_on();
    write(1, "\r", 1);
    write(1, "\x1b[2J", 4); 
    write(1, "\x1b[1;1H", 6);
}
