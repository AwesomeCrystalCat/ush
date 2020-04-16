#include "ush.h"

static void replace_env_end(t_st *st, char *head, char *res, char *tail) {
    char *tmp = NULL;

    tmp = mx_strjoin(head, res);
    free(st->cmd);
    st->cmd = mx_strjoin(tmp, tail);
    head ? free(head) : 0;
    tail ? free(tail) : 0;
    tmp ? free(tmp) : 0;
    res ? free(res) : 0;
}

static void replace_env(t_st *st, int i, char *head, char *tail) {
    char *tmp = NULL;
    char *res = NULL;
    int k = i + 1;

    i != 0 ? head = mx_strndup(st->cmd, i) : 0;
    if (st->cmd[k] == '{') {
        for (; st->cmd[k] != '}' && st->cmd[k]; k++);
        tmp = strndup(&st->cmd[i + 2], k - i - 2);
        tail = mx_strdup(&st->cmd[k + 1]);
    }
    else {
        tmp = mx_get_env(st->cmd, k);
        tail = mx_strdup(&st->cmd[k + mx_strlen(tmp)]);
    }
    res = mx_check_env(st->env, tmp);
    res == NULL ? res = mx_check_env(st->set, tmp) : 0;
    free(tmp);
    replace_env_end(st, head, res, tail);
}

static void replace_pwd(t_st *st, int i, char *head, char *tail) {
    char *tmp = NULL;

    i != 0 ? head = mx_strndup(st->cmd, i) : 0;
    if (st->cmd[i + 1] == '+' || st->cmd[i + 1] == '-') {
        tail = strdup(&st->cmd[i + 2]);
        if (st->cmd[i + 1] == '+')
            tmp = mx_strjoin(head, getenv("HOME"));
        else if (st->cmd[i + 1] == '-')
            tmp = mx_strjoin(head, getenv("OLDPWD"));
    }
    else {
        tail = strdup(&st->cmd[i + 1]);
        tmp = mx_strjoin(head, getenv("PWD"));
    }
    free(st->cmd);
    st->cmd = mx_strjoin(tmp, tail);
    head ? free(head) : 0;
    tail ? free(tail) : 0;
    free(tmp);
}

void mx_replace_cmd(t_st *st) { // Для алиасов и тильды вначале пробел Для баксов проверка на парность слэша ( и фиг скобки
    for (int i = 0; st->cmd[i] != '\0'; i++) {
        if (st->cmd[i] == '$' && st->cmd[i + 1] != '('
            && mx_check_slash(st->cmd, i) == 0) {
            replace_env(st, i, NULL, NULL);
        }
        if (st->cmd[i] == '~'
            && ((st->cmd[i - 1] == ' ' && i != 0) || i == 0)
            && (((st->cmd[i + 1] == '-' || st->cmd[i + 1] == '+')
            && (st->cmd[i + 2] == ' ' || st->cmd[i + 2] == '/'
            || st->cmd[i + 2] == '\0')) || (st->cmd[i + 1] == '\0'
            ||  st->cmd[i + 1] == '/' || st->cmd[i + 1] == ' '))) {
            replace_pwd(st, i, NULL, NULL);
        }
    }
}
