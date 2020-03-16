#include "libmx.h"

void mx_pop_front(t_list **head) {
    t_list *ptr = NULL;

    if (head != NULL && *head != NULL) {
        ptr = *head;
        *head = ptr->next;
        free(ptr);
    }
    return;
}
