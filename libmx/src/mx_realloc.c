#include "libmx.h"

 void *mx_realloc(void *ptr, size_t size) {
     void *newstr = NULL;
     size_t ptr_size = malloc_size(ptr);

     if (ptr == NULL)
         return malloc(size);
     else if (ptr_size > size) {
         newstr = malloc(size);
         mx_memcpy(newstr, ptr, size);
         free(ptr);
         }
     else if (ptr_size < size) {
         newstr = malloc(ptr_size);
         mx_memcpy(newstr, ptr, ptr_size);
         free(ptr);
     }
     else
         free(ptr);
     return newstr;
 }
