#include <mlib.h>

MList_t *mlist_first(MList_t *list) {
    if(list) {
        for(;list->prev; list = list->prev);
        return list;
    }

    return NULL;
}

static MList_t *mlist_create(mpointer_t data) {
    MList_t *list = (MList_t *) calloc(1, sizeof(MList_t));
    list->data = data;

    return list;
}

MList_t *mlist_append(MList_t *list, mpointer_t data) {
    MList_t *_list = mlist_create(data);

    if(!list) {
        return _list;
    }

    list->next = _list;
    _list->prev = list;

    return _list;
}

MList_t *mlist_remove(MList_t *list, mconstpointer_t data) {
    list = mlist_first(list);

    while(list && list->data != data)
        list = list->next;

    if(list) {
        MList_t *next = list->next;
        MList_t *prev = list->prev;
        free(list);

        if(next) next->prev = prev;
        if(prev) prev->next = next;

        if(prev) return prev;
        if(next) return next;
    }

    return NULL;
}

void mlist_remove_all(MList_t *list) {
    list = mlist_first(list);

    while(list) {
        MList_t *item = list;
        list = list->next;
        free(item);
    }
}

MList_t *mlist_find(MList_t *list, mconstpointer_t data) {
    list = mlist_first(list);

    while(list && list->data != data)
        list = list->next;

    return list;
}

void mlist_foreach(MList_t *list, MListForeach func) {
    list = mlist_first(list);
    while(list) {
        func(list->data);
        list = list->next;
    }
}