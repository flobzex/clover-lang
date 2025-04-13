#include <clover/list.h>

#include <stdlib.h>
#include <errno.h>


bool
clv_list_push (struct clv_list **root, void *ptr) {
    struct clv_list *node = malloc (sizeof (*node));

    if (node == NULL) {
        return false;
    }

    node->ptr = ptr;

    if (root != NULL) {
        node->next = *root;
    }

    *root = node;

    return true;
}

void *
clv_list_pop (struct clv_list **root) {
    if (root == NULL) {
        return NULL;
    }

    struct clv_list *node = *root;
    void *ptr = node->ptr;
    *root = (*root)->next;

    free (node);

    return ptr;
}

bool
clv_list_remove (struct clv_list **root, void *value) {
    struct clv_list *prev = NULL;
    struct clv_list *temp = (*root);

    while (temp != NULL) {
        if (temp->ptr == value) {
            if (temp == (*root)) {
                *root = (*root)->next;
            } else {
                prev->next = temp->next;
            }

            free (temp);
            return true;
        }

        prev = temp;
        temp = temp->next;
    }

    return false;
}

size_t
clv_list_length (struct clv_list *root) {
    size_t length = 0;

    while (root != NULL) {
        root = root->next;
        length++;
    }

    return length;
}

void
clv_list_iterate (struct clv_list *root, void (*callback)(void *)) {
    while (root != NULL) {
        callback (root->ptr);
        root = root->next;
    }
}

void
clv_list_clear (struct clv_list **root, void (*_free_data)(void *)) {
    if (root == NULL) {
        return;
    }

    struct clv_list *curr = *root;
    struct clv_list *temp;

    while (curr != NULL) {
        if (_free_data) {
            _free_data (curr->ptr);
        }

        temp = curr->next;
        free (curr);

        curr = temp;
    }

    *root = NULL;
}
