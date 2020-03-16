#include "libmx.h"

static void swap_strings(char **s1, char **s2) {
    char *temp = *s1;

    *s1 = *s2;
    *s2 = temp;
}

static int partition(char **arr, int left, int right, int *count) {
    int mid = left + (right - left) / 2;
    int pivot = mx_strlen(arr[mid]);

    while (left <= right) {
        while (mx_strlen(arr[left]) < pivot)
            left++;
        while (mx_strlen(arr[right]) > pivot)
            right--;
        if (left <= right) {
            if (mx_strlen(arr[left]) != mx_strlen(arr[right]))
                swap_strings(&arr[left], &arr[right]);
            if (left != right)
                (*count)++;
            left++;
            right--;
        }
    }
    return left;
}

int mx_quicksort_origin(char **arr, int left, int right) {
    int count = 0;
    int pivot = 0;

    if (arr) {
        if (left < right) {
            pivot = partition(arr, left, right, &count);
            if (left < pivot - 1)
                mx_quicksort_origin(arr, left, pivot - 1);
            if (pivot < right)
                mx_quicksort_origin(arr, pivot, right);
        }
        return count;
    }
    return -1;
}
