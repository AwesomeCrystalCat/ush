#include "ush.h"

static char *cmd_del_spaces(char *cmd) {
    char *tmp = NULL;
    int n = mx_strlen(cmd) - 1;
    int start = 0;
    int end = 0;

    if (cmd[start] == '{') {
        for (;(cmd[start] == '{' || cmd[start] == ' ')
        && cmd[start] != '\0'; start++);
    }
    if (cmd[n] == '}') {
        for (;(cmd[n] == '}' || cmd[n] == ' ') && n != 0; n--)
            end++;
    }
    if (start || end) {
        tmp = mx_strndup(&cmd[start], mx_strlen(&cmd[start]) - end);
        free(cmd);
        return tmp;
    }
    return cmd;
}

int mx_command_pars(t_st *st, char *c, int j, int k) {
    int bufsize = 64;
    char **tokens = malloc(bufsize * sizeof(char*));

    !tokens ? mx_malloc_err() : 0;
    c = cmd_del_spaces(c);
    for (int i = 0; c[i] != '\0'; i++) {
        if (c[i] == '|' || c[i] == '(' || c[i] == ')' || c[i] == '$'
            || c[i] == '`' || c[i] == '<' || c[i] == '>') {
            tokens[k++] = strndup(&c[i], 1);
        }
        else if (c[i] != ' ') {
            tokens[k++] = strndup(&c[i], strcspn(&c[i], " <>|()$`"));
            i += strcspn(&c[i], " <>|()$`") - 1;
        }
        k >= bufsize ? tokens = mx_split_backup(tokens, bufsize) : 0;
        k >= bufsize ? bufsize += 64 : 0;
    }
    tokens[k] = NULL;
    return mx_streams(st, tokens);
}
