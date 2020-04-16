#include "ush.h"

char **mx_split_backup(char **tokens, int bufsize) {
    char **tokens_backup = NULL;

    bufsize += 64;
    tokens_backup = tokens;
    tokens = realloc(tokens, bufsize * sizeof(char*));
    if (!tokens) {
        free(tokens_backup);
        mx_malloc_err();
    }
    return tokens;
}
