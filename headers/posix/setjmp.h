/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	File:				setjmp.h
 *							©1993-1996 metrowerks Inc. All rights reserved
 *	Author:			Andreas Hommel
 *
 *	Content:		Interface to setjmp/longjmp ANSI functions ...
 */

#ifndef __csetjmp__
#define __csetjmp__

#pragma direct_destruction off

#include <ansi_parms.h>

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
	int _Setjmp(jmp_buf);
	
#else

	typedef long *jmp_buf[13];			/*	D3-D7,PC,A2-A6,SP,__local_destructor_chain */

#endif

#if __dest_os == __powertv_os

	int		setjmp(jmp_buf);
	
#elif __POWERPC__

	int		__setjmp(jmp_buf);
	void	longjmp (jmp_buf,int);

#else

	int		setjmp (jmp_buf);
	void	longjmp(jmp_buf,int);

#endif

void __longjmp_ldestr(jmp_buf,int);

__end_extern_c

#if __dest_os == __be_os
	typedef long *sigjmp_buf[(sizeof(jmp_buf)/sizeof(int)) + (32*4)];

	int  sigsetjmp(sigjmp_buf jmp, int savemask);
    void siglongjmp(sigjmp_buf jmp, int val);

#endif

__end_namespace(stdc_space(setjmp))

__import_stdc_into_std_space(setjmp)

#pragma options align=reset
#pragma direct_destruction reset

#endif

/*     Change record
960829 bkoz added l.you's changes for powerTV

960917 KO: Moved the __extern_c block up here so it now encloses
           the Intel function declaration.
*/
