#include "libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    t_list *ptr = NULL;
    int i = 1;

    if (lst == NULL)
        return NULL;
    ptr = lst;
    while (i == 1) {
        i = 0;
        while (ptr->next != NULL) {
            if (cmp(ptr->data, ptr->next->data) == 0) {
                mx_swap_list(ptr, ptr->next);
                i = 1;
            }
            ptr = ptr->next;
        }
        ptr = lst;
    }
    return ptr;
}
