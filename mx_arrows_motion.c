#include "ush.h"

static void up_motion(t_config* term, t_hist **hist) {
    if (term->total > 0) {
        if (term->out->line != NULL) {
            free(term->out->line);
            term->out->len = 0;
        }
        term->out->line = mx_strndup(hist[term->total - 1]->line,
                                     hist[term->total - 1]->len);
        term->out->len = hist[term->total - 1]->len;
        mx_refresh_line(term, 5);
        write(1, hist[term->total - 1]->line,
              hist[term->total - 1]->len);
        write(1, "\x1b[0J", strlen("\x1b[0J"));
        term->pos = hist[term->total - 1]->len;
        term->mo_y = hist[term->total - 1]->len + 1;
        term->total--;
    }
}

static void clean_up(t_config* term) {
    free(term->out->line);
    term->out->line = NULL;
    term->out->len = 0;
    term->pos = 0;
}

static void down_motion(t_config* term, t_hist **hist) {
    if (term->total < term->entry - 1) {
        if (term->out->line != NULL)
            clean_up(term);
        term->out->line = mx_strndup(hist[term->total + 1]->line,
                                     hist[term->total + 1]->len);
        term->out->len = hist[term->total + 1]->len;
        mx_refresh_line(term, 5);
        write(1, hist[term->total + 1]->line, hist[term->total + 1]->len);
        write(1, "\x1b[0J", strlen("\x1b[0J"));
        term->pos = hist[term->total + 1]->len;
        term->mo_y = hist[term->total + 1]->len + 1;
        term->total++;
    }
    else if (term->total == term->entry - 1) {
        clean_up(term);
        mx_refresh_line(term, 5);
        write(1, "\x1b[0J", strlen("\x1b[0J"));
        term->mo_y = 1;
        term->total++;
    }
}

static void create_history(t_config* term, t_hist **hist) {
    if (hist[0]->line == NULL) {
        char tmp[1024];
        FILE *fp;

        if ((fp = fopen (".file.txt", "r"))) {
            fgets(tmp, 1024, (FILE*)fp);
            fclose(fp);
        }
        if (strlen(tmp)) {
            char *token = strtok(tmp, "\t");

            for (int i = 0; token != NULL; i++, term->entry++) {
                hist[i]->line = mx_strdup(token);
                hist[i]->len = strlen(hist[i]->line);
                token = strtok(NULL, "\t");
            }
            free(token);
            term->total = term->entry;
        }
    }
}

void mx_arrows_motion(int k, t_config* term, t_hist **hist) {
    if (k == MX_ARROW_UP || k == MX_ARROW_DOWN)
        create_history(term, hist);
    switch (k) {
        case MX_ARROW_LEFT:
            if (term->mo_y > 1)
                term->mo_y--;
            break;
        case MX_ARROW_RIGHT:
            if (term->mo_y < term->out->len + 1)
                term->mo_y++;
            break;
        default:
            if (hist[0]->line != NULL) {
                if (k == MX_ARROW_UP)
                    up_motion(term, hist);
                else if (k == MX_ARROW_DOWN)
                    down_motion(term, hist);
            }
            break;
    }
}
