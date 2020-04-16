#include "ush.h"

char *mx_check_env(char **arr, char *macros) {
    int n = mx_strlen(macros);
    char *res = NULL;

    for (int i = 0; arr[i] != NULL; i++) {
        if ((strncmp(arr[i], macros, n) == 0)
            && arr[i][n] == '=') {
            res = mx_strdup(&arr[i][n + 1]);
        }
    }
    return res;
}
