#include "ush.h"

static char *split_tok(char *line, int i, int j, char delim) {
    char *token = NULL;
    char *tmp = NULL;

    if (delim == '\0' || delim == ';')
        token = strndup(&line[j], i - j);
    if (delim == '|' || delim == '&')
        token = strndup(&line[j], i - j - 1);
    tmp = token;
    token = mx_del_extra_spaces(token);
    free(tmp);
    return token;
}

char **mx_split_line(char *line, int bufsize, int j, int k) {
    char **tokens = malloc(bufsize * sizeof(char*));

    !tokens ? mx_malloc_err() : 0;
    for (int i = 0; j != -1; i++) {
        line[i] == '|' ? i++ : 0;
        line[i] == '&' ? i++ : 0;
        if (i != 0 && (line[i] == '|' || line[i] == '&'
            || line[i] == ';' || line[i] == '\0')) {
            if (mx_check_slash(line, i) == 0) { // 0 - ok
                tokens[k++] = split_tok(line, i, j, line[i]);
                tokens[k++] = strndup(&line[i], 1);
                j = i + 1;
            }
        }
        line[i] == '\0' ? j = -1 : 0;
        k >= bufsize ? tokens = mx_split_backup(tokens, bufsize) : 0;
        k >= bufsize ? bufsize += 64 : 0;
    }
    tokens[k] = NULL;
    return tokens;
}
