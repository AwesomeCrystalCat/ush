#include "libmx.h"

void mx_push_front(t_list **list, void *data) {
    t_list *nextnode = NULL;

    if (list != NULL) {
        nextnode = mx_create_node(data);
        nextnode->next = *list;
        *list = nextnode;
    }
}
