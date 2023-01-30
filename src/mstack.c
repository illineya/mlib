#include <mlib.h>

MStack_t *mstack_init() {
    return (MStack_t *) calloc(1, sizeof(MStack_t));
}

void mstack_push(MStack_t *stack, mpointer_t data) {
    stack->list = mlist_append(stack->list, data);
    stack->count++;
}

mpointer_t mstack_pop(MStack_t *stack) {
    if(stack && stack->list) {
        stack->list = mlist_last(stack->list);
        mpointer_t item = stack->list->data;
        stack->list = mlist_remove(stack->list, item);
        stack->count--;

        return item;
    }
    return NULL;
}

void mstack_deinit(MStack_t *stack) {
    if(stack) {
        mlist_remove_all(stack->list);
        free(stack);
    }
}