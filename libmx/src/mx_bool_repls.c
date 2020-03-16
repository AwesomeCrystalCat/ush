#include "libmx.h"

_Bool repls(char **new_s, char *old_s, char *sub_s, char *repl) {
    int sub_s_len = mx_strlen(sub_s);
    int replace_len = mx_strlen(repl);
    int old_s_len = mx_strlen(old_s);
    int index = mx_get_substr_index(old_s, sub_s);
    if(index != -1) {
        
        *new_s = mx_strnew((old_s_len - sub_s_len) + replace_len);
        mx_strncpy(*new_s, old_s, index);
        mx_strcat(*new_s, repl);
        mx_strcat(*new_s, &old_s[index + sub_s_len]);
        return 1;
    }
    *new_s = mx_strdup(old_s);
    return 0;
}


