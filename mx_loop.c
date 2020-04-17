#include "ush.h"

void mx_loop(t_st *st) {
    st->cmd = strdup("${USER}ius\\\\||pwd ~+ |pwd ~-/;((cd ..; a.txt < pwd>b.txt \\~ && (echo .. \\; ${111}45) | $(cd ~ || pwd)) &&    { `pwd` ||pwd $123  }");
    //st->cmd = strdup("\\\\${PATH}123");
    //st->cmd = strdup("~$USER");
    //st->cmd = strdup(" ~+/ \\${111}89.$USER\\\\");
    //st->cmd = strdup("1&&{2||{3;4}&&5};6;7&&8||9&&0;{{123}};{ { {321}  };{456;789} }");
    //st->cmd = strdup("pwd;pwd");
    char **commands = NULL;

    //while (st->status) {

        printf("COMMANDS before = %s\n", st->cmd);

        mx_replace_cmd(st); // ~ $

        st->commands = mx_split_line(st->cmd, 64, 0, 0); // ; || &&

//        for (int i = 0; st->commands[i] != NULL; i++) {
//            printf("cmd %d = %s\n", i, st->commands[i]);
//        }

        printf("COMMANDS after = %s\n", st->cmd);


        st->status = mx_simple_commands(st, st->commands, st->cmd, 0);

        free(st->cmd);
        free(commands);
    //}
}
