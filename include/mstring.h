#ifndef __MSTRING_H__
#define __MSTRING_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif

muint32_t mstr_hash(mconstpointer_t);
mboolean mstr_equal(mconstpointer_t, mconstpointer_t);

#endif