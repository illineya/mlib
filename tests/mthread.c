#include <mlib.h>
#include <stdio.h>

static void mthread_test_run(mpointer_t udata) {
    udata[0] = '2';
}

mboolean mthread_test_create(mpointer_t udata) {
    muchar_t str[] = "1";

    mboolean status = FALSE;
    MThread_t *thread = mthread_create(mthread_test_run, (mpointer_t) str);
    mthread_join(thread);
    if(str[0] == '2')
        status = TRUE;
    mthread_deinit(thread);

    return status;
}

mboolean mthread_test_detached(mpointer_t udata) {
    muchar_t str[] = "1";

    MThread_t *thread = mthread_create(mthread_test_run, (mpointer_t) str);
    mboolean status = mthread_detach(thread);
    mthread_deinit(thread);

    return status;
}

int main() {
    MTest_t *test = mtest_init();
    mtest_append(test, "mthread_test_create", mthread_test_create);
    mtest_append(test, "mthread_test_detached", mthread_test_detached);
    mint32_t failed = mtest_run(test, NULL);
    mtest_deinit(test);

    return failed;
}