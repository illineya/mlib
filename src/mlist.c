#include <mlib.h>
#include <stdlib.h>

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

mpointer_t mlist_get(MList_t *list, muint32_t n) {
    if(list) {
        list = mlist_first(list);
        for(int i=0; list; list = list->next, i++) {
            if(i == n) {
                return list->data;
            }
        }
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

MList_t *mlist_insert_sorted(MList_t *list, mpointer_t data, MSortFunc func) {
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
    MList_t *first = mlist_first(list);

    while(first && first->data != data)
        first = first->next;

    if(first) {
        MList_t *next = first->next;
        MList_t *prev = first->prev;
        free(first);

        if(next) next->prev = prev;
        if(prev) prev->next = next;

        if(prev) return prev;
        if(next) return next;

        return NULL;
    }

    return list;
}

void mlist_remove_all(MList_t *list) {
    list = mlist_first(list);

    while(list) {
        MList_t *item = list;
        list = list->next;
        free(item);
    }
}

void mlist_remove_all_full(MList_t *list) {
    list = mlist_first(list);

    while(list) {
        MList_t *item = list;
        list = list->next;
        free(item->data);
        free(item);
    }
}

void mlist_remove_all_full2(MList_t *list, MFreeFunc func) {
    list = mlist_first(list);

    while(list) {
        MList_t *item = list;
        list = list->next;
        func(item->data);
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

void mlist_foreach(MList_t *list, MForeachFunc func, mpointer_t udata) {
    list = mlist_first(list);

    while(list) {
        if(!func(NULL, list->data, udata))
            break;
        list = list->next;
    }
}
