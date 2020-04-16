#include "ush.h"

//static char *mx_get_link_path(char *path) {
//    char *link_path = malloc(1024);
//    int len = 0;
//
//    if ((len = readlink(path, link_path, sizeof(link_path) - 1)) == -1) {
//        return 0;
//    }
//    link_path[len] = 0;
//    return link_path;
//}

static char *get_pwd() {
    char *pwd = mx_strdup(getenv("PWD"));
    char *cwd = getcwd(NULL, 0);
    char *link_path = 0;

    if (pwd == 0)
        return cwd;
//    if (mx_is_link(pwd)) {
//        link_path = mx_get_link_path(pwd);
//        pwd = mx_del_last_rank(pwd);
//        pwd = mx_strjoin3(mx_strjoin2(pwd, "/"), link_path);
//        if (mx_strcmp(pwd, cwd) == 0) {
//            free(cwd);
//            free(pwd);
//            return mx_strdup(getenv("PWD"));
//        }
//    }
    //free(pwd);
    return cwd;
}

char **mx_set_arr() {
    char **arr = (char**)malloc(sizeof(char*) * 2);

    arr[0] = mx_strdup("111=777");
    arr[1] = NULL;
    return arr;
}

char **mx_alias_arr() {
    char **arr = (char**)malloc(sizeof(char*) * 2);

    arr[0] = mx_strdup("fc=echo fuck");
    arr[1] = NULL;
    return arr;
}

t_st *mx_init_struct(char **env) {
    t_st *st = (t_st*) malloc(sizeof(t_st));

    st->env = env;
    st->set = mx_set_arr();
    st->alias = mx_alias_arr();
    //st->processes = 0; // empty
    //st->is_exit = false;
    st->status = 0;
    st->pwd = mx_strdup(getenv("PWD"));
    st->pwd_p = getcwd(NULL, 0);
    st->pwd_l = mx_strdup(st->pwd);
    st->pwd_old = mx_strdup(getenv("OLDPWD"));
    st->pwd_home = mx_strdup(getenv("HOME"));

//    signal(SIGSEGV, mx_segfault_in);
//    signal(SIGINT, mx_ctrl_c);
//    signal(SIGTSTP, mx_ctrl_z);
    return st;
}
