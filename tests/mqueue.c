#include <mlib.h>
#include <string.h>

mboolean mtest_queue_push_one(mpointer_t udata) {
    MQueue_t **queue = (MQueue_t **) udata;

    mqueue_push(*queue, "test");
    mpointer_t data = mqueue_pop(*queue);
    if(!strcmp(data, "test")) {
        return TRUE;
    }

    return FALSE;
}

mboolean mtest_queue_push_multiple(mpointer_t udata) {
    MQueue_t **queue = (MQueue_t **) udata;

    mqueue_push(*queue, "test");
    mqueue_push(*queue, "lost");
    mpointer_t data = mqueue_pop(*queue);
    if(!strcmp(data, "test")) {
        return TRUE;
    }

    return FALSE;
}

int main() {
    MQueue_t *queue = mqueue_init();
    MTest_t *test = mtest_init();
    mtest_append(test, "mtest_queue_push_one", mtest_queue_push_one);
    mtest_append(test, "mtest_queue_push_multiple", mtest_queue_push_multiple);
    mint32_t failed = mtest_run(test, (mpointer_t) &queue);
    mqueue_deinit(queue);
    mtest_deinit(test);

    return failed;
}