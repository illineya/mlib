#include <mlib.h>
#include <string.h>

mboolean mtest_async_queue_push_one(mpointer_t udata) {
    MAsyncQueue_t **queue = (MAsyncQueue_t **) udata;

    masync_queue_push(*queue, "test");
    mpointer_t data = masync_queue_pop(*queue);
    if(!strcmp(data, "test")) {
        return true;
    }

    return false;
}

mboolean mtest_async_queue_push_multiple(mpointer_t udata) {
    MAsyncQueue_t **queue = (MAsyncQueue_t **) udata;

    masync_queue_push(*queue, "test");
    masync_queue_push(*queue, "lost");
    mpointer_t data = masync_queue_pop(*queue);
    if(!strcmp(data, "test")) {
        return true;
    }

    return false;
}

int main() {
    MAsyncQueue_t *queue = masync_queue_init();
    MTest_t *test = mtest_init();
    mtest_append(test, "mtest_async_queue_push_one", mtest_async_queue_push_one);
    mtest_append(test, "mtest_async_queue_push_multiple", mtest_async_queue_push_multiple);
    mint32_t failed = mtest_run(test, (mpointer_t) &queue);
    masync_queue_deinit(queue);
    mtest_deinit(test);

    return failed;
}