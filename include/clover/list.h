#ifndef CLOVER_LIST_H_
#define CLOVER_LIST_H_

#include <clover/base.h>

typedef struct clv_list clv_list_t;

typedef void (*clv_list_func_t)(void *data);

clv_list_t *clv_list_new       ();
bool        clv_list_push_back (clv_list_t *list, void *ptr);
bool        clv_list_pop_back  (clv_list_t *list, void **out_ptr);
size_t      clv_list_length    (clv_list_t *list);
void        clv_list_foreach   (clv_list_t *list, clv_list_func_t callback);
void        clv_list_clear     (clv_list_t *list, clv_list_func_t _free_ptr);
void        clv_list_free      (clv_list_t *list, clv_list_func_t _free_ptr);

#endif /* CLOVER_LIST_H_ */
