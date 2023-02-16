#include <mlib.h>

MThread_t *mthread_create(MThreadFunc func, mpointer_t udata) {
    MThread_t *thread = malloc(sizeof(MThread_t));
    if(thread) {
        thread->id = pthread_create(&thread->thread, NULL, (void *) func, udata);
        if(!thread->id) {
            thread->detached = FALSE;
            return thread;
        }
        free(thread);
    }
    return NULL;
}

mboolean mthread_detach(MThread_t *thread) {
    if(thread) {
        thread->detached = TRUE;
        return pthread_detach(thread->thread) == 0;
    }
    return TRUE;
}

mboolean mthread_join(MThread_t *thread) {
    if(thread) {
        return pthread_join(thread->thread, NULL) == 0;
    }
    return TRUE;
}

void mthread_deinit(MThread_t *thread) {
    if(thread) {
        mthread_join(thread);
        pthread_cancel(thread->thread);
        free(thread);
    }
}