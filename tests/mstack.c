#include <mlib.h>
#include <string.h>

mboolean mtest_stack_push_one(mpointer_t udata) {
    MStack_t **stack = (MStack_t **) udata;

    mstack_push(*stack, "test");
    mpointer_t data = mstack_pop(*stack);
    if(!strcmp(data, "test")) {
        return TRUE;
    }

    return FALSE;
}

mboolean mtest_stack_push_multiple(mpointer_t udata) {
    MStack_t **stack = (MStack_t **) udata;

    mstack_push(*stack, "test");
    mstack_push(*stack, "lost");
    mpointer_t data = mstack_pop(*stack);
    if(!strcmp(data, "lost")) {
        return TRUE;
    }

    return FALSE;
}

int main() {
    MStack_t *stack = mstack_init();
    MTest_t *test = mtest_init();
    mtest_append(test, "mtest_stack_push_one", mtest_stack_push_one);
    mtest_append(test, "mtest_stack_push_multiple", mtest_stack_push_multiple);
    mint32_t failed = mtest_run(test, (mpointer_t) &stack);
    mstack_deinit(stack);
    mtest_deinit(test);

    return failed;
}