#include <mlib.h>
#include <stdio.h>

MQueue_t *mqueue_init(void) {
    MQueue_t *queue = (MQueue_t *) calloc(1, sizeof(MQueue_t));
    queue->list = NULL;
    return queue;
}

void mqueue_push(MQueue_t *queue, mpointer_t data) {
    queue->list = mlist_append(queue->list, data);
    queue->count++;
}

mpointer_t mqueue_pop(MQueue_t *queue) {
    if(queue && queue->list) {
        queue->list = mlist_first(queue->list);
        mpointer_t item = queue->list->data;
        queue->list = mlist_remove(queue->list, item);
        queue->count--;

        return item;
    }
    return NULL;
}

void mqueue_deinit(MQueue_t *queue) {
    if(queue) {
        mlist_remove_all(queue->list);
        free(queue);
    }
}
