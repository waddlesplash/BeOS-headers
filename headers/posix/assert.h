/*
 *	assert.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
*/

#pragma options align=mac68k

#include <ansi_parms.h>

#undef assert

#ifdef NDEBUG

#define assert(condition) ((void) 0)

#else

__extern_c

void __assertion_failed(char * condition, char * filename, int lineno);

__end_extern_c

#define assert(condition) ((condition) ? ((void) 0) : __assertion_failed(#condition, __FILE__, __LINE__))

#endif /* def NDEBUG */

#pragma options align=reset
