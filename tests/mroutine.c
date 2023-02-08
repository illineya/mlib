#include <mlib.h>
#include <stdio.h>

void mroutine_test_attach(mpointer_t data) {
    printf("VAR: %s %lu\n", data, pthread_self());
}

mboolean mroutine_test_create(mpointer_t udata) {
    mroutine_attach((MRoutine_t *) udata, mroutine_test_attach, "Hello World!", NULL);

    return TRUE;
}

int main() {
    MTest_t *test = mtest_init();
    MRoutine_t *routine = mroutine_init();

    mtest_append(test, "mroutine_test_create", mroutine_test_create);
    mtest_append(test, "mroutine_test_create", mroutine_test_create);
    mtest_append(test, "mroutine_test_create", mroutine_test_create);
    mtest_append(test, "mroutine_test_create", mroutine_test_create);

    mtest_append(test, "mroutine_test_create", mroutine_test_create);
    mtest_append(test, "mroutine_test_create", mroutine_test_create);
    mtest_append(test, "mroutine_test_create", mroutine_test_create);
    mtest_append(test, "mroutine_test_create", mroutine_test_create);

    mint32_t failed = mtest_run(test, (mpointer_t) routine);

    sleep(1);

    mroutine_deinit(routine);
    mtest_deinit(test);

    return failed;
}