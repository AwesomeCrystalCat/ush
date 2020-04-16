#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ush.h"

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

char *builtin_str[] = {
        "cd",
        "help",
        "exit"
};

int (*builtin_func[]) (char **) = {
        &lsh_cd,
        &lsh_help,
        &lsh_exit
};

int lsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    }
    else {
        if (chdir(args[1]) != 0)
            perror("lsh");
    }
    return 1;
}

int lsh_help(char **args) {
    int i;

    printf("The following are built in:\n");
    for (i = 0; i < lsh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }
    printf("Use the man command for information on other programs.\n");
    return 1;
}

int lsh_exit(char **args) {
    return 0;
}

int lsh_launch(char **args) {
    pid_t pid;
    int status = 1;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1)
            perror("lsh");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
        perror("lsh");
    while (!WIFEXITED(status) && !WIFSIGNALED(status))
        waitpid(pid, &status, WUNTRACED);
    return 1;
}

int lsh_execute(char **args) {
    int i;

    if (args[0] == NULL) // An empty command was entered.
        return 1;
    for (i = 0; i < lsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0)
            return (*builtin_func[i])(args);
    }
    return lsh_launch(args);
}






int main(int argc, char **argv, char **env) {
    t_st *st = mx_init_struct(env);
//    for (int i = 0; env[i] != NULL; i++)
//        printf("%s\n", env[i]);
    mx_loop(st);
    return 0;
}
