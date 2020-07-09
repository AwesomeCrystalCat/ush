#include "ush.h"

char *mx_strdup(const char *str) {
    return mx_strcpy(mx_strnew(strlen(str)), str);
}
