#ifndef CLOVER_LIST_H_
#define CLOVER_LIST_H_

#include <clover/base.h>

struct clv_list {
    struct clv_list *next;

    void *ptr;
};

bool   clv_list_push    (struct clv_list **root, void *ptr);
void  *clv_list_pop     (struct clv_list **root);
bool   clv_list_remove  (struct clv_list **root, void *ptr);
size_t clv_list_length  (struct clv_list *root);
void   clv_list_iterate (struct clv_list *root, void (*callback)(void *));
void   clv_list_clear   (struct clv_list **root, void (*_free_data)(void *));

#endif /* CLOVER_LIST_H_ */
