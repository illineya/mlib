#ifndef __MSTRING_H__
#define __MSTRING_H__

#if !defined (__MLIB_H_INSIDE__)
#error "Only <mlib.h> can be included directly."
#endif

muint32_t mstr_hash(const char *str);
mboolean mstr_equal(const char *, const char *);

#endif