#include "ush.h"

static void answer_is(char *str) {
    if (!strcmp("pwd -L -P", str))
        write(1, " - to find the way if you're lost", 33);
    else if (!strcmp("cd -s, -P", str))
        write(1, " - to check some wild places", 28);
    else if (!strcmp("echo -n, -E, -e", str))
        write(1, " - to get the answer", 20);
    else if (!strcmp("which -a, -s", str))
        write(1, " - to find the command lost", 24);
    else if (!strcmp("env -i, -u", str))
        write(1, " - to see what's in the environment", 34);
    else if (!strcmp("export", str))
        write(1, " - to add smth to the environment", 33);
    else if (!strcmp("unset", str))
        write(1, " - to move smth from the environment", 36);
    else if (!strcmp("alias", str))
        write(1, " - to create a command on your favor", 36);
    else if (!strcmp("exit", str))
        write(1, " - to leave this place", 22);
    else if (!strcmp("history", str))
        write(1, " - to look up the breadcrumbs", 29);
}

void mx_help(void) {
    char *command[12] = {"pwd -L -P", "cd -s, -P", "echo -n, -E, -e",
                          "which -a, -s", "env -i, -u", "export",
                          "unset", "alias", "history", "exit", "clear"};
    write(1, "Hello, stranger! Choose any function on your favor:", 51);
    for (int i = 0; i < 10; i++) {
        write(1, "\n        ", 9);
        write(1, "\x1b[1m\x1b[34m", strlen("\x1b[1m\x1b[34m"));
        write(1, command[i], strlen(command[i]));
        write(1, "\x1b[0m", strlen("\x1b[0m"));
        if (strlen(command[i]) < 15) {
            for (int j = 0; j < 15 - (int)strlen(command[i]); j++)
                write(1, " ", 1);
        }
        answer_is(command[i]);
    }
}
