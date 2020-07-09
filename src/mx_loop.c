#include "ush.h"

static void clean_up(t_config* term) {
    fflush(stdout);
    free(term->out->line);
    free(term->out->tail);
    free(term->quo);
    term->out->tail = NULL;
    term->out->line = NULL;
    term->quo = NULL;
    term->quo = (int *)malloc(sizeof(int) * 2);
    term->quo[0] = 0;
    term->quo[1] = 0;
    term->q_id = 0;
    term->out->len = 0;
    term->pos = 0;
}

static void reset(t_config* term, t_hist **hist) {
    term->reset = 0;
    write(1, "\n\r", 2);
    write(1, "\x1b[0J", 4);
    mx_cooked_mode_on();
    tcsetattr(0, TCSAFLUSH, &term->origin);
    write(1, hist[term->entry]->line, hist[term->entry]->len);
    term->entry++;
    term->total = term->entry;
    clean_up(term);
    mx_raw_mode_on();
    write(1, "\r\n", 2);
    term->mo_x = term->mo_x + 2;
    mx_refresh_line(term, 5);
}

static void inner_loop(t_config* term, t_hist **hist) {
    mx_get_term_params(term);
    write(1, "\x1b[?25h", 6);
    mx_process_key(term, hist);
    write(1, "\x1b[?25l", 6);
    mx_get_cursor(&term->y, &term->x);
    term->mo_x = term->x;
    if (!term->quo[0])
        mx_refresh_screen(term, 5);
    else
        mx_refresh_screen(term, 12);
    if (term->reset)
        reset(term, hist);
}

void mx_loop(t_config* term, t_hist **hist) {
    mx_get_commands(term);
    mx_get_term_params(term);
    mx_raw_mode_on();
    mx_get_cursor(&term->y, &term->x);
    term->mo_x = term->x;
    term->mo_y = term->y;
    mx_refresh_line(term, 5);
    while (1)
        inner_loop(term, hist);
    mx_cooked_mode_on();
    tcsetattr(0, TCSAFLUSH, &term->origin);
}
