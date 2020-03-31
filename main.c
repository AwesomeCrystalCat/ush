#include "ush.h"

char *read_line(void) {
    int buff = 1024;
    int i = 0;
    char *buffer = (char *)malloc(sizeof(char) * buff);
    int chr;

    while (1) {
        chr = getchar();
        if (chr == EOF || chr == '\n') {
            buffer[i] = '\0';
            return buffer;
        }
        else
            buffer[i++] = chr;
        if (i >= buff) {
            buff += 1024;
            buffer = realloc(buffer, buff);
        }
    }
}

int main(int argc, char **argv, char **envp) 
{
    char **args =  NULL;
    char **line = malloc(sizeof(*line)); //change this num later
    int i = -1;

    while (1) {
    printf("u$h> ");
    line[++i] = read_line();
    // for (int j = 0; j <= i; j++)
    //     printf("%s\n", line[j]);
    line = realloc(line, (sizeof(*line) * (2 + i)));

        // args = lsh_split_line(line);
        // status = lsh_execute(args);

        // free(line);
        // free(args);
        if (!strcmp(line[i], "env")) {
            for (int num = 0; envp[num] != NULL; num++) {
                printf("\n%s", envp[num]); 
            }
            printf("\n");
        }
        if (!strcmp(line[i], "pwd"))
            printf("%s\n", getenv("PWD"));
        if (!strcmp(line[i], "exit"))
            exit(0);
        printf("co");
    }
    return 0;
}
