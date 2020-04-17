#include "ush.h"

int mx_simple_commands(t_st *st, char **commands, char *line, int passed_cmd) {

    for (int i = 0; commands[i] != NULL; i++) {
        if (i % 2 == 0 && commands[i][0] != '\0') {
            printf("command = %s\n", commands[i]);
            st->status = mx_command_pars(st, commands[i], 0, 0); //status 0 = next command execute
        }
        else {
            if ((commands[i][0] == '|' || commands[i][0] == '&')
                && commands[i + 1][0] == '{')
                i += mx_complex_cmd(st, commands, i, i); // Возвращает след активную команду { }
            else if ((commands[i][0] == '|' && st->status == 0)
                || (commands[i][0] == '&' && st->status == 1))
                i += 2;
            printf("i = %d status = %s\n\n", i, commands[i]);
            // Check for {} in line and choose active command + status
        }
    }
    return 1;
}
