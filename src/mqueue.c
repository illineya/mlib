#include <mlib.h>

MQueue_t *mqueue_init() {
    return (MQueue_t *) calloc(1, sizeof(MQueue_t));
}

void mqueue_push(MQueue_t *queue, mpointer_t data) {
    MList_t *current = mlist_append(queue->head, data);
    if(!queue->head)
        queue->head = current;
    queue->tail = current;
    queue->count++;
}

mpointer_t mqueue_pool(MQueue_t *queue) {
    mpointer_t item = queue->head->data;
    mlist_remove(queue->head, queue->head->data);
    queue->count--;
    return item;
}

void mqueue_deinit(MQueue_t *queue) {
    if(queue) {
        mlist_remove_all(queue->head);
        free(queue);
    }
}