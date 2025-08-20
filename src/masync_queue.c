#include <mlib.h>
#include <string.h>

MAsyncQueue_t *masync_queue_init(void) {
    MAsyncQueue_t *queue = (MAsyncQueue_t *) calloc(1, sizeof(MAsyncQueue_t));
    queue->queue = mqueue_init();

    pthread_mutex_init(&queue->mutex, NULL);
    pthread_mutex_init(&queue->wait, NULL);

    return queue;
}

void masync_queue_push(MAsyncQueue_t *queue, mpointer_t data) {
    if(queue) {
        pthread_mutex_lock(&queue->mutex);
        mqueue_push(queue->queue, data);
        pthread_mutex_unlock(&queue->mutex);

        pthread_mutex_unlock(&queue->wait);
    }
}

mpointer_t masync_queue_pop(MAsyncQueue_t *queue) {
    if(queue && queue->queue) {
        pthread_mutex_lock(&queue->wait);

        pthread_mutex_lock(&queue->mutex);
        mpointer_t data = mqueue_pop(queue->queue);
        if(mqueue_length(queue->queue) > 0) {
            pthread_mutex_unlock(&queue->wait);
        }
        pthread_mutex_unlock(&queue->mutex);

        return data;
    }
    return NULL;
}

muint32_t masync_queue_length(MAsyncQueue_t *queue) {
    muint32_t len = 0;
    if(queue) {
        pthread_mutex_lock(&queue->mutex);
        len = mqueue_length(queue->queue);
        pthread_mutex_unlock(&queue->mutex);
    }
    return len;
}

void masync_queue_deinit(MAsyncQueue_t *queue) {
    if(queue) {
        mqueue_deinit(queue->queue);
        pthread_mutex_destroy(&queue->mutex);
        pthread_mutex_destroy(&queue->wait);
        free(queue);
    }
}
