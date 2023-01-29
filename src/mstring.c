#include <mlib.h>
#include <string.h>

muint32_t mstr_hash(mconstpointer_t str) {
    muint32_t hash = 0;

    if(str)
        while(*str++)
            hash += (hash << 3) + hash + *str;

    return hash;
}

mboolean mstr_equal(mconstpointer_t a, mconstpointer_t b) {
    if(!a && !b) return TRUE;
    if(!a || !b) return FALSE;

    return strcmp(a, b) == 0;
}