/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	assert.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
*/


#include <ansi_parms.h>

#undef assert

#ifdef NDEBUG

#define assert(condition) ((void) 0)

#else

#ifndef __cassert__
#define	__cassert__

__namespace(__stdc_space(assert))

__extern_c

void __assertion_failed(char * condition, char * testfilename, int lineno);

__end_extern_c

__end_namespace(__stdc_space(assert))

__import_stdc_into_std_space(assert)

#endif /* __cassert__ */

#define assert(condition) ((condition) ? ((void) 0) : __std(__assertion_failed)(#condition, __FILE__, __LINE__))

#endif /* def NDEBUG */

#pragma options align=reset
/*     Change record
*/
