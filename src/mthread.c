#include <mlib.h>

MThread_t *mthread_create(MThreadFunc func, mpointer_t udata) {
    MThread_t *thread = malloc(sizeof(MThread_t));
    thread->id = pthread_create(&thread->thread, NULL, (void *) func, udata);
    thread->detached = FALSE;
    return thread;
}

mboolean mthread_detach(MThread_t *thread, mboolean detach) {
    thread->detached = detach;
    return pthread_detach(thread->thread) > 0;
}

mboolean mthread_join(MThread_t *thread) {
    return pthread_join(thread->thread, NULL) > 0;
}
