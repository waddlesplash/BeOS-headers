/*
 *   setjmp.h -- ANSI 
 *
 *   Functions and type for setting up and executing non-local jumps.
 *
 *           Copyright (c) 1990, MetaWare Incorporated
 */

#ifndef _SETJMP_H
#define _SETJMP_H

#ifdef __CPLUSPLUS__
extern "C" {
#endif

#if _IBM370 && _AIX
#    define _JBLEN 32
#elif _RT || _IBM370 || _ENGINE
#    define _JBLEN 16
#elif _I386
#    if _AIX || _BSD
#        define _JBLEN 22
#    elif _SUN
#        define _JBLEN 8
#    elif _MSDOS
#	 define _JBLEN 15
#    elif _OS2
#	 define _JBLEN 7
#    elif _MSNT
#	 define _JBLEN 8
#	 define setjmp	_setjmp
#    elif _SOL || _ATT4
#	 define _JBLEN 10
#    else
#        define _JBLEN 6
#    endif
#elif _AM29K
#    define _JBLEN 4
#elif _MC68		/*Assuming Sun 3*/
#    define _JBLEN 58
#elif defined _NM || defined _I860
#    define _JBLEN 137 /* MW uses: 29=15 int regs, 14 float regs.  AT&T:137. */
#elif defined _NAM
#    define _JBLEN 64   /* 32 local and 32 global regs */
#elif defined _SPARC	/* Solaris requires 12 */
#    define _JBLEN 12	
#elif defined _NEXT
#    define _JBLEN 39	
#elif defined _SGL
#    define _JBLEN 46	/* 46 * 4 = 184 */
#elif defined _HOBBIT
#    define _JBLEN 2
#elif defined _R3000	/* aka VMIP, R2000 & R3000 */
#    define _JBLEN 28
#elif _UPA
#    define _JBLEN 50
#elif _RS6000
#    define _JBLEN 64	/* Rs6k */
#else
#    define _JBLEN 16
#    error jmp_buf length is not known!!
#endif


#if !_I386 || !_MSNT
#undef setjmp
#endif


#if _UPA
    typedef double	jmp_buf[_JBLEN/2];
#else
    typedef int 	jmp_buf[_JBLEN];
#endif
extern  int     setjmp(jmp_buf __buf);
extern  void    longjmp(jmp_buf __buf, int __val);

#ifdef __CPLUSPLUS__
}
#endif
#endif /*_SETJMP_H*/
