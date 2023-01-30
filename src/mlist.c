#include <mlib.h>
#include <stdio.h>

MList_t *mlist_first(MList_t *list) {
    if(list) {
        for(;list->prev; list = list->prev);
        return list;
    }

    return NULL;
}

MList_t *mlist_last(MList_t *list) {
    if(list) {
        for(;list->next; list = list->next);
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
    list = mlist_last(list);

    if(!list) {
        return _list;
    }

    list->next = _list;
    _list->prev = list;

    return _list;
}

MList_t *mlist_prepend(MList_t *list, mpointer_t data) {
    MList_t *_list = mlist_create(data);
    list = mlist_first(list);

    if(!list) {
        return _list;
    }

    _list->next = list;
    list->prev = _list;

    return _list;
}

static MList_t *mlist_insert_before(MList_t *list, mpointer_t data) {
    MList_t *current = mlist_create(data);
    current->next = list;
    current->prev = list->prev;
    list->prev = current;

    return list;
}

MList_t *mlist_insert_sorted(MList_t *list, mpointer_t data, MListSortFunc func) {
    list = mlist_first(list);

    while(list->next) {
        if(func(list->data, data) >= 0) {
            return mlist_insert_before(list, data);
        }
        list = list->next;
    }
    mlist_append(list, data);

    return list;
}

MList_t *mlist_remove(MList_t *list, mconstpointer_t data) {
    list = mlist_first(list);

    while(list && list->data != data)
        list = list->next;

    if(list) {
        MList_t *next = list->next;
        MList_t *prev = list->prev;
        free(list->data);
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
        free(item->data);
        free(item);
    }
}

muint32_t mlist_length(MList_t *list) {
    MList_t *first = mlist_first(list);
    muint32_t len = 0;

    for(; first; first = first->next, len++);
    return len;
}

MList_t *mlist_find(MList_t *list, mconstpointer_t data) {
    list = mlist_first(list);

    while(list && list->data != data)
        list = list->next;

    return list;
}

void mlist_foreach(MList_t *list, MListForeachFunc func, mpointer_t udata) {
    list = mlist_first(list);

    while(list) {
        if(!func(list->data, udata))
            break;
        list = list->next;
    }
}
