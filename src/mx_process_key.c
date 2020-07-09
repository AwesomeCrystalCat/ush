#include "ush.h"

static void arrow_keys(t_config *term, t_hist **hist, int c) {
    switch (c) {
        case MX_BACKSPACE:
            mx_backspace_action(term);
            break;
        case MX_HOME_KEY:
            term->mo_y = 1;
            break;
        case MX_END_KEY:
            term->mo_y = term->out->len + 1;
            break;
        case MX_ARROW_DOWN: //fallthrough
        case MX_ARROW_UP: //fallthrough
        case MX_ARROW_RIGHT: //fallthrough
        case MX_ARROW_LEFT: //fallthrough
            mx_arrows_motion(c, term, hist);
            break;
        default:
            break;
    }
}

void mx_process_key(t_config *term, t_hist **hist) {
    int c = mx_read_key();

    switch (c) {
        case '\r':
            mx_return_action(term, hist);
            break;
        case '\t':
            mx_tab_action(term);
            break;
        case CTRL_KEY('l'):
            mx_clear_screen(term);
            break;
        case CTRL_KEY('d'):
            write(1, "\x1b[0J", 4);
            mx_cooked_mode_on();
            tcsetattr(0, TCSAFLUSH, &term->origin);
            write (1, "\n", 1);
            exit(0);
            break;
        default:
            if ((c >= 1000 && c <= 1008) || c == 127)
                arrow_keys(term, hist, c);
            else
                mx_editor_processing(term, c);
            break;
    }
}
