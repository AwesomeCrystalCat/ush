#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *ptr = NULL;

    if (*list == NULL) {
        *list = mx_create_node(data);
        return;
    }
    ptr = *list;
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = mx_create_node(data);
}
