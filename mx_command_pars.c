#include "ush.h"

int mx_command_pars(t_st *st, char *c, int j, int k) {
    int bufsize = 64;
    char **tokens = malloc(bufsize * sizeof(char*));

    !tokens ? mx_malloc_err() : 0;
    for (int i = 0; c[i] != '\0'; i++) {
        if (c[i] == '|' || c[i] == '(' || c[i] == ')' || c[i] == '{'
            || c[i] == '}' || c[i] == '<' || c[i] == '>'
            || c[i] == '$' || c[i] == '`') {
            tokens[k++] = strndup(&c[i], 1);
        }
        else if (c[i] != ' ') {
            tokens[k++] = strndup(&c[i], strcspn(&c[i], " <>|{}()$`"));
            i += strcspn(&c[i], " <>|{}()$`") - 1;
        }
        k >= bufsize ? tokens = mx_split_backup(tokens, bufsize) : 0;
        k >= bufsize ? bufsize += 64 : 0;
    }
    tokens[k] = NULL;
    return mx_streams(st, tokens);
}
