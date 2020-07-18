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

static void sig_action(t_config *term) {
    if (term->out->line != NULL) {
        free(term->out->line);
        term->out->line = NULL;
        term->out->len = 0;
    }
    write(1, "\x1b[0J", 4);
    write (1, "\n", 1);
    term->mo_x++;
    mx_get_cursor(&term->y, &term->x);
    term->mo_x = term->x;
    mx_refresh_line(term, 5);
}

void mx_process_key(t_config *term, t_hist **hist) {
    int c = mx_read_key();

    if (c == '\r')
        mx_return_action(term);
    else if (c == '\t')
        mx_tab_action(term);
    else if (c == CTRL_KEY('l'))
        mx_clear_screen(term);
    else if (c == CTRL_KEY('g'))
        write(1, "\a", 1);
    else if (c == CTRL_KEY('c'))
        sig_action(term);
    else if (c == CTRL_KEY('d'))
        sig_action(term);
    else if ((c >= 1000 && c <= 1008) || c == 127)
        arrow_keys(term, hist, c);
    else if (c >= 32 && c <= 126)
        mx_editor_processing(term, c);
}
