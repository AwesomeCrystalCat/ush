#include "libmx.h"

void mx_pop_back(t_list **head) {
    t_list *ptr = NULL;

    if (head != NULL && *head != NULL) {
        ptr = *head;
        if (ptr->next == NULL) {
            free(ptr);
            *head = NULL;
            return;
        }
        else {
            while (ptr->next->next != NULL)
                ptr = ptr->next;
            free(ptr->next);
            ptr->next = NULL;
        }
    }
    return;
}
