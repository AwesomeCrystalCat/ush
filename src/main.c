#include "ush.h"
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <termcap.h>
#include <term.h>
#include <curses.h>
#include <ctype.h>

int main(int argc, char **argv, char **envp) {
    (void)envp;
    (void)argv;
    (void)argc;
    t_config *term = mx_config_init();
    t_hist **hist = (t_hist **)malloc(sizeof(t_hist) * 200);

    if (isatty(0))
        mx_loop(term, hist);
    return 0;
}
