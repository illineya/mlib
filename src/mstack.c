#include <mlib.h>

MStack_t *mstack_init() {
    return (MStack_t *) calloc(1, sizeof(MStack_t));
}

void mstack_push(MStack_t *stack, mpointer_t data) {
    MList_t *current = mlist_append(stack->head, data);
    if(!stack->head)
        stack->head = current;
    stack->tail = current;
    stack->count++;
}

mpointer_t mstack_pool(MStack_t *stack) {
    mpointer_t item = stack->tail->data;
    mlist_remove(stack->head, stack->tail->data);
    stack->count--;
    return item;
}

void mstack_deinit(MStack_t *stack) {
    if(stack) {
        mlist_remove_all(stack->head);
        free(stack);
    }
}