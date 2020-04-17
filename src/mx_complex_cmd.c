#include "ush.h"

int mx_complex_cmd(t_st *st, char **commands, int cur, int passed_cmd) {
    int open = 0;
    int close = 0;

    if ((commands[cur][0] == '&' && st->status == 1)
        || (commands[cur][0] == '|' && st->status == 0)) {
        for (; commands[cur + 1] != NULL; cur += 2) {
            for (int i = 0; commands[cur + 1][i] != '\0'; i++) {
                if (commands[cur + 1][i] == '{')
                    open++;
                if (commands[cur + 1][i] == '}')
                    close++;
            }
            if (close - open == 0)
                break;
        }
        return cur - passed_cmd + 2;
    }
    return 0;
}
