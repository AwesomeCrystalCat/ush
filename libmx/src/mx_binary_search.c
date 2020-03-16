#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    unsigned int mid;
    unsigned int start = 0;
    unsigned int end = size - 1;

    if (arr && s && size > 0) {
        *count = 0;
        while (start <= end) {
            mid = start + (end - start) / 2;
            ++*count;
            if (mx_strcmp(arr[mid], s) == 0)
                return mid;
            else if (mx_strcmp(arr[mid], s) < 0)
                start = mid + 1;
            else
                end = mid - 1;
        }
        *count = 0;
        return -1;
    }
    return 0;
}
