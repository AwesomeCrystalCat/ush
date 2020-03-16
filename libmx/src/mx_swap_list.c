#include "libmx.h"

void mx_swap_list(t_list *a, t_list *b) {
    void *tmp = NULL;

    tmp = a->data;
    a->data = b->data;
    b->data = tmp;
}
