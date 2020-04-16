#include "ush.h"

int mx_check_slash(char *line, int end) {
    int count = 0;

    if (line[end] == '&' || line[end] == '|')
        end--;
    for (; line[end] == '\\' && end != -1; end--)
        count++;
    if (count % 2 == 0)
        return 0;
    else
        return 1;
}
