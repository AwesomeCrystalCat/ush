#include "libmx.h"

char *mx_file_to_str(const char *file) {
    int fp = open(file, O_RDONLY);
    int len = 0;
    char *s = NULL;
    char buff;

    if (read(fp, NULL, 0) < 0 || fp == -1)
        return NULL;
    while (read(fp, &buff, 1))
        len++;
    close(fp);
    fp = open(file, O_RDONLY);
    s = mx_strnew(len);
    read(fp, s, len);
    close(fp);
    return s;
}
