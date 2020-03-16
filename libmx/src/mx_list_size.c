#include "libmx.h"

int mx_list_size(t_list *list) {
    t_list *ptr = list;
    unsigned int count = 0;

    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }
    return count;
}
