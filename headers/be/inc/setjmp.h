/*
 *	File:				setjmp.h
 *							©1993-1995 metrowerks Inc. All rights reserved
 *	Author:			Andreas Hommel
 *
 *	Content:		Interface to setjmp/longjmp ANSI functions ...
 */

#ifndef __SETJMP__
#define __SETJMP__

#pragma options align=mac68k
#pragma direct_destruction off

#if __POWERPC__

	typedef long *jmp_buf[70];
	
	#define setjmp(jmp_buf)	__setjmp(jmp_buf)

#else

	typedef long *jmp_buf[13];			/*	D3-D7,PC,A2-A6,SP,__local_destructor_chain */

#endif

#ifdef __cplusplus
extern "C" {
#endif

#if __POWERPC__

	int		__setjmp(jmp_buf);
	void	longjmp (jmp_buf,int);

#else

	int		setjmp (jmp_buf);
	void	longjmp(jmp_buf,int);

#endif

void __longjmp_ldestr(jmp_buf,int);

#ifdef __cplusplus
}
#endif

#pragma options align=reset
#pragma direct_destruction reset

#endif
