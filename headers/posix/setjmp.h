/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	File:				setjmp.h
 *							©1993-1997 metrowerks Inc. All rights reserved
 *	Author:			Andreas Hommel
 *
 *	Content:		Interface to setjmp/longjmp ANSI functions ...
 */

#ifndef __csetjmp__
#define __csetjmp__

#include <ansi_parms.h>

/* #pragma options align=native */
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif
#pragma direct_destruction off

__namespace(__stdc_space(setjmp))

__extern_c	/* 960917 */

#if __dest_os == __powertv_os

	typedef long *jmp_buf[64];

#elif __POWERPC__

	typedef long *jmp_buf[70];
	
	#define setjmp(jmp_buf)	__setjmp(jmp_buf)

#elif	__INTEL__

	typedef int jmp_buf[10];
	
	#define setjmp(jmp_buf) _Setjmp(jmp_buf)
	_IMPEXP_ROOT int _Setjmp(jmp_buf); /* Be-mani 980107 */
	
#else

	typedef long *jmp_buf[13];			/*	D3-D7,PC,A2-A6,SP,__local_destructor_chain */

#endif

#if __dest_os == __powertv_os

	int		setjmp(jmp_buf);
	
#elif __POWERPC__

#ifndef __SETJMP_NOT_INTERNAL__
#pragma internal on
#endif

	_IMPEXP_ROOT int		__setjmp(jmp_buf); /* Be-mani 980107 */

#ifndef __SETJMP_NOT_INTERNAL__
#pragma internal reset
#endif

	_IMPEXP_ROOT void	longjmp (jmp_buf,int); /* Be-mani 980107 */

#elif __CFM68K__

#ifndef __SETJMP_NOT_INTERNAL__
#pragma internal on
#endif

	int		setjmp(jmp_buf);

#ifndef __SETJMP_NOT_INTERNAL__
#pragma internal reset
#endif

	void	longjmp(jmp_buf,int);

#else

	_IMPEXP_ROOT int		setjmp (jmp_buf); /* Be-mani 980107 */
	_IMPEXP_ROOT void	longjmp(jmp_buf,int); /* Be-mani 980107 */

#endif

void __longjmp_ldestr(jmp_buf,int);

__end_extern_c

#if __dest_os == __be_os
	typedef long *sigjmp_buf[(sizeof(jmp_buf)/sizeof(int)) + (32*4)];      /* mm 970708 */

	_IMPEXP_ROOT int  sigsetjmp(sigjmp_buf jmp, int savemask); /* mm 970708 */ /* Be-mani 980107 */
    _IMPEXP_ROOT void siglongjmp(sigjmp_buf jmp, int val); /* mm 970708 */ /* Be-mani 980107 */

#endif

__end_namespace(stdc_space(setjmp))

__import_stdc_into_std_space(setjmp)

#pragma direct_destruction reset
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
/* #pragma options align=reset */

#endif

/*     Change record
 * 960829 bkoz added l.you's changes for powerTV

 * 960917 KO: Moved the __extern_c block up here so it now encloses
           the Intel function declaration.
 * mm 970708  Inserted Be changes
 * Be-mani 980107 Merge Be shared lib changes
 */
