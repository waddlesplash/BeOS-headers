/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	assert.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
*/


#include <ansi_parms.h>

/* #pragma options align=native */
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#undef assert

#ifdef NDEBUG

#define assert(condition) ((void) 0)

#else

#ifndef __cassert__
#define	__cassert__

__namespace(__stdc_space(assert))

__extern_c

_IMPEXP_ROOT void __assertion_failed(char * condition, char * testfilename, int lineno); /* 980107 Be-mani */

__end_extern_c

__end_namespace(__stdc_space(assert))

__import_stdc_into_std_space(assert)

#endif /* __cassert__ */

#define assert(condition) ((condition) ? ((void) 0) : __std(__assertion_failed)(#condition, __FILE__, __LINE__))

#endif /* def NDEBUG */

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
/* #pragma options align=reset */
/*     Change record
 * 980107	Be-mani	Be shared library additions.
*/
