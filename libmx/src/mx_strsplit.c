#include "libmx.h"

static int count_chars(const char *s, char c) {    
    int i = 0;

    while (s[i] != c && s[i] != '\0')
        i++;
    return i;
}

char **mx_strsplit(const char *s, char c) {
    if (s) {
        int len = mx_count_words(s, c);
        int depth = 0;
        int elem = 0;
        char **arr = (char **)malloc(sizeof(char *) * (len + 1));

        for (int i = 0; i < mx_strlen(s); i++) {
            while (s[i] == c)
                i++;
            if (s[i] != c) {
                depth = count_chars(&s[i], c);
                arr[elem] = mx_strndup(&s[i], depth);
                i = i + depth;
                elem++;
            }
        }
        arr[len] = NULL;
        return arr;
    }
    return NULL;
}
