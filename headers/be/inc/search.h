/*
 *   search.h -- extra-ANSI 
 *
 *   Sorting and searching functions.
 *
 *           Copyright (c) 1990, MetaWare Incorporated
 */

#ifndef _SEARCH_H
#define _SEARCH_H

#ifdef __CPLUSPLUS__
extern "C" {
#endif

extern void * _lfind (void * __key, void * __start,
                    unsigned * __kount, unsigned __wid,
                    int (* __cmp)(const void * __data1, const void * __data2));

extern void * _lsearch (void * __key, void * __start,
                    unsigned * __kount, unsigned __wid,
                    int (* __cmp)(const void * __data1, const void * __data2));

#include <_na.h>
#if _NA_NAMES
    _NA(lfind)
    _NA(lsearch)
#elif _MSDOS && __HIGHC__
    extern void * lfind (void * __key, void * __start,
            unsigned * __kount, unsigned __wid,
            int (* __cmp)(const void * __data1, const void * __data2));

    extern void * lsearch (void * __key, void * __start,
            unsigned * __kount, unsigned __wid,
            int (* __cmp)(const void * __data1, const void * __data2));
#endif


#if __HIGHC__

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
typedef unsigned int size_t;
#endif

extern  void * bsearch(const void *__key, const void *__base,
                      size_t __nmemb, size_t __size,
                      int (*__compar)(const void *, const void *));

extern  void qsort(void *__base, size_t __nmemb, size_t __size,
                  int (*__compar)(const void *, const void *));
#endif  /* __HIGHC__ */


#ifdef __CPLUSPLUS__
}
#endif
#endif /* _SEARCH_H */
