/*
 *   malloc.h -- extra-ANSI 
 *
 *   Memory-allocation functions.
 *
 *           Copyright (c) 1990, MetaWare Incorporated
 */

#ifndef _MALLOC_H
#define _MALLOC_H

#ifdef __CPLUSPLUS__
extern "C" {
#endif

#ifndef _SIZE_T_DEFINED
#   include "sizet.h"
#endif

#if _OS2 || _MSNT
    #define _VM 1
#else
    #define _VM 0
#endif

#if _MSDOS
    extern void _ffree(void _Far *);
    extern void _nfree(_Near void *);
    extern void _Far *_fmalloc(size_t);
    extern void _Far *_frealloc(void _Far *, size_t);
    extern void _Near *_nmalloc(size_t);
    extern size_t _coreleft();
    extern size_t _coretotal();
#endif

#ifdef __PENPOINT__
    extern  void *	_smalloc(size_t __size);
    extern  void	_sfree(void *__ptr);
#endif

#if __HIGHC__
    #if _MSDOS || _OS2 || _MSNT
	/*
	 * This MUST be included for "alloca(n)" to work.
	 */
	#define alloca(n) _Alloca(n)
	#define _alloca(n) _Alloca(n)

	/* heap status */
	#define _HEAPEMPTY	(-1)
	#define _HEAPOK 	(-2)
	#define _HEAPBADBEGIN	(-3)
	#define _HEAPBADNODE	(-4)
	#define _HEAPEND	(-5)
	#define _HEAPBADPTR	(-6)

	/* heap use flags */
	#define _FREEENTRY	0
	#define _USEDENTRY	1

	typedef struct _heapinfo {
	    void *_pentry;		/* heap entry pointer */
	    size_t _size;		/* size of heap entry */
	    int _useflag;		/* heap flags */
	    void *_reserved1; 		/* reserved area */
	    } _HEAPINFO;

	extern int _heapwalk(_HEAPINFO *entryinfo);
	extern int _heapset(unsigned int fill);
	extern int _heapchk();
    #endif

    extern void * calloc(size_t, size_t);
    extern void free(void *);
    extern void * malloc(size_t);
    extern void * realloc(void *, size_t);
#endif

#ifdef __CPLUSPLUS__
}
#endif
#endif /* _MALLOC_H */
