#include "ush.h"

void mx_cooked_mode_on(void) {
    struct termios raw;

    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &raw) == -1)
        mx_die("tcsetattr");
}
