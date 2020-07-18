#include "ush.h"

static bool comparator(const char *name) {
    bool is_dir = 0;

    if (strcmp(name, ".") == 0)
        is_dir = 1;
    if (strcmp(name, "..") == 0)
        is_dir = 1;
    return is_dir;
}

static int count_processor(DIR *mydir) {
    struct dirent *myfile;
    int count = 0;

    while((myfile = readdir(mydir)) != NULL) {
        if (myfile->d_name[0] != '.' && comparator(myfile->d_name) == 0)
            count++;
    }
    return count;
}

static void add_our_command(t_config *term, int i) {
    char *command[8] = {"cd", "env", "export", "unset",
                        "alias", "history", "exit", "clear"};

    for (int j = 0; j < 8; j++)
        term->command[i++] = mx_strdup(command[j]);
}

void mx_get_commands(t_config *term) {
    struct dirent *dirptr;
    DIR *mydir;
    int i = 0;

    if ((mydir = opendir("/bin")) != NULL)
        term->count = count_processor(mydir);
    closedir(mydir);
    term->command = (char **)malloc(sizeof(char *) * (term->count + 8));
    if ((mydir = opendir("/bin")) != NULL) {
        while((dirptr = readdir(mydir)) != NULL) {
            if (dirptr->d_name[0] != '.'
                && comparator(dirptr->d_name) == 0)
                term->command[i++] = mx_strdup(dirptr->d_name);
        }
    }
    closedir(mydir);
    add_our_command(term, i);
}
