/*
 *   stddef.h -- ANSI 
 *
 *   Various useful macros and types.
 *
 *           Copyright (c) 1990, MetaWare Incorporated
 */

#ifndef _STDDEF_H
#define _STDDEF_H

#ifdef __CPLUSPLUS__
extern "C" {
#endif

#ifndef _PTRDIFF_T_DEFINED
#define _PTRDIFF_T_DEFINED
typedef int ptrdiff_t;
#endif

#ifndef _SIZET_H
#include <sizet.h>
#endif

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
typedef _wchar_t wchar_t;
#endif

#ifndef NULL
#define NULL            ((void *)0)
#endif

#ifndef offsetof
#define offsetof(T,I)   ((size_t)((char *)&((T*)0)->I-(char *)0))
#endif

#if defined(_REENTRANT) && (_MSNT || _OS2)	/* if multi-thread */
    extern unsigned long __threadid(void);
    #ifndef _threadid
	#define _threadid (__threadid())
    #endif
#endif

#ifdef __CPLUSPLUS__
}
#endif
#endif /*_STDDEF_H*/
