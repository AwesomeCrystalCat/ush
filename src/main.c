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
    t_hist **hist = mx_hist_init();

    // create_history(hist);
    // for (int i = 0; i < 4; i++) {
    //     write(1, hist[i]->line, hist[i]->len);
    //     write(1, "\n", 1);
    // }

    if (isatty(0))
        mx_loop(term, hist);
    return 0;
}
