#include "ush.h"
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <termcap.h>
#include <term.h>
#include <curses.h>
#include <ctype.h>
#include <signal.h>

// static void mx_init_signals(void) {
//     sigset_t mask;

//     sigfillset(&mask);
//     sigdelset(&mask, SIGINT);
//     sigdelset(&mask, EOF);
//     sigdelset(&mask, SIGTSTP);
//     sigprocmask(SIG_SETMASK, &mask, NULL);
// }

int main(int argc, char **argv, char **envp) {
    (void)argv;
    (void)envp;
    (void)argc;
    t_config *term = mx_config_init();
    t_hist **hist = mx_hist_init();

    // mx_init_signals();
    if (isatty(0)) {
        mx_loop(term, hist, envp);
    }
    return 0;
}
