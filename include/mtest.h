#ifndef __MTEST_H__
#define __MTEST_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif

typedef mboolean (* MTestFunc)(mpointer_t udata);

typedef struct MTest MTest_t;
struct MTest {
    MList_t *list;
    muint8_t length;
};

MTest_t *mtest_init(void);
void mtest_deinit(MTest_t *);
void mtest_append(MTest_t *test, mchar_t *name, MTestFunc func);
mint32_t mtest_run(MTest_t *test, mpointer_t udata);

#endif