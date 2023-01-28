#include <mlib.h>
#include <stdio.h>

int main() {
    MList_t *list = NULL;
    list = mlist_append(list, "Hello");
    list = mlist_append(list, " ");
    list = mlist_append(list, "World");



    return 0;
}