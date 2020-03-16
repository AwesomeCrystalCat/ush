#include "libmx.h"

int mx_bubble_sort(char **arr, int size) {
    char *str = NULL;
    int i;
    int j;
    int count = 0;

    if (arr && size > 0) {
        for (i = 0; i < size - 1; i++) {
            for (j = 0; j < size - i - 1; j++) {
                if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
                    str = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = str;
                    count++;
                }
            }
        }
        return count;
    }
    return 0;
}
