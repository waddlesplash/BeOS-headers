/*
 *   alloca.h -- non-ANSI 
 *
 *   This file MUST be included for "alloca(n)" to work.
 *
 *           Copyright (c) 1991, MetaWare Incorporated
 */

#ifndef _ALLOCA_H
#define _ALLOCA_H

#ifdef __CPLUSPLUS__
extern "C" {
#endif

/*
 * NOTE:
 * alloca(n) is not an ANSI-defined library function.
 * Nevertheless, on many architectures, it cannot be supported unless the
 * compiler is able to generate inline code for it.
 * Therefore, we define the special macro "_ALLOC", which tells the compiler
 * to "recognize" alloca as a builtin, in the same manner as memcpy and
 * abs() are recognized.
 *
 * However, this only works for those front-ends built since May 7, 1991.
 */
#ifndef _ALLOCA
#    define _ALLOCA _ALLOCA
#endif

#if defined _ALLOCA || !defined __HIGHC__ 
    extern void *alloca(unsigned n);
#else
#   define alloca(n) _Alloca(n)		/* Old way of doing it. */
#endif

#ifdef __CPLUSPLUS__
}
#endif
#endif /*_ALLOCA_H*/
