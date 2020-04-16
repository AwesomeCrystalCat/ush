#include "ush.h"

int mx_simple_commands(t_st *st, char **commands, char *line, int status) {

    for (int i = 0; commands[i] != NULL; i++) {
        if (i % 2 == 0) {
            printf("command = %s\n", commands[i]);
            st->status = mx_command_pars(st, commands[i], 0, 0); //status 0 = next command execute
        }
        else {
            if ((commands[i][0] == '|' || commands[i][0] == '&')
                && commands[i + 1][0] == '{') {
                st->status = mx_complex_cmd(st, commands, i); // Возвращает количество команд что нужно пропустить(не выполнять их из-за фиг скобок)
            }
            printf("status = %s\n\n", commands[i]);
            // Check for {} in line and choose active command + status
            status = 1;
        }
    }
    return 1;
}
