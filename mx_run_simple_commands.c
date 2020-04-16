#include "ush.h"

int mx_simple_commands(t_st *st, char **commands, char *line, int status) {

    for (int i = 0; commands[i] != NULL; i++) {
        if (status && i % 2 == 0) {
            printf("command = %s\n", commands[i]);
            status = mx_command_pars(st, commands[i], 0, 0); //status 1 = next command execute
        }
        else {
            printf("status = %s\n\n", commands[i]);
            // Check for {} in line and choose active command + status
            status = 1;
        }
    }
    return 1;
}
