#include "ush.h"

static void replace_pwd_env(t_st *st, char **tokens, int i) {
    for (int i = 0; tokens[i] != NULL; i++) {
        if (tokens[i][0] == '$' || tokens[i][0] == '~') {
            replace_pwd_env(st, tokens, i);
        }
    }
}

void mx_replace_tok(t_st *st, char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        if ((tokens[i][0] == '$' && tokens[i + 1][0] != '(')
            || tokens[i][0] == '~') {
            replace_pwd_env(st, tokens, i);
        }
    }
}
