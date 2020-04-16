#include "ush.h"

void mx_loop(t_st *st) {
    st->cmd = strdup("${USER}ius\\\\||pwd ~+ |pwd ~-/;((cd ..; a.txt < pwd>b.txt \\~ && (echo .. \\; ${111}45) | $(cd ~ || pwd)) &&    { `pwd` ||pwd $123  }");
    //st->cmd = strdup("\\\\${PATH}123");
    //st->cmd = strdup("~$USER");
    //st->cmd = strdup(" ~+/ \\${111}89.$USER\\\\");
    char **commands = NULL;
    int status = 1;

    while (status) {

        printf("COMMANDS before = %s\n", st->cmd);

        mx_replace_cmd(st);

        st->commands = mx_split_line(st->cmd, 64, 0, 0);

        printf("COMMANDS after = %s\n", st->cmd);


        status = mx_simple_commands(st, st->commands, st->cmd, 1);

        free(st->cmd);
        free(commands);
        status = 0;
    }
}
