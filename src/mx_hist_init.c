#include "ush.h"

t_hist **mx_hist_init(void) {
    t_hist **hist = (t_hist **)malloc(sizeof(t_hist) * 200);

    for (int i = 0; i < 200; i++) {
        hist[i] = (t_hist *)malloc(sizeof(t_hist) * 1);
        hist[i]->line = NULL;
    }
    return hist;
}
