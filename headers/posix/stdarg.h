/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	stdarg.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __cstdarg__
#define __cstdarg__

#include <ansi_parms.h>

__namespace(__stdc_space(stdarg))

#include <va_list.h>

/* #pragma options align=native */
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#define va_start(ap, parm)	ap = __va_start(parm)
#define va_end(ap)

#if __INTEL__

#define __va_start(parm)	(__std(va_list)) ((long)(&parm) + \
							((((long)(&parm + 1) - (long)(&parm))+3)/4*4))  /* mm 9708027 */
#define _Align(type, mask) (sizeof(type) + (mask) & ~(mask))
#define va_arg(ap, type)	(* (type *) (((ap) += _Align(type, 3)) - _Align(type, 3)))

#elif	__POWERPC__ && (__dest_os	==	__mac_os)  /*for PowerMac 32bit calling conventions only*/
#define __va_start(parm)	(__std(va_list)) (&parm + 1)  /* mm 9708027 */
#define va_arg(ap, type)  (*       (((type *) (ap += (((sizeof(type)+3)/4)*4) )) -1)        )

#else

#define __va_start(parm)	(__std(va_list)) ((char *)&parm + (sizeof (parm) + (1U) & ~(1U)))  /* mm 9708027 */
#define va_arg(ap, type)	(*       (((type *) (ap += sizeof(type))) - 1)        )

#endif

__end_namespace(stdc_space(stdarg))

__import_stdc_into_std_space(stdarg)

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
/* #pragma options align=reset */

#endif /* __cstdarg__ */
/*     Change record
961015	bkoz	change to va_arg according to BR ES56366 (J. Pratt)
061216	KO		Fixed va_start for Intel.
mm 9708027      Fixed va_start to allow for unsigned char arguments.  BR7931
*/
