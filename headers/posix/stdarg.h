/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	stdarg.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __cstdarg__
#define __cstdarg__

#include <ansi_parms.h>

__namespace(__stdc_space(stdarg))

#if __INTEL__
#pragma pack(push, 8)
#endif

#include <va_list.h>

#define __va_start(parm)	(__std(va_list)) (&parm + 1)

#define va_start(ap, parm)	ap = __va_start(parm)
#define va_end(ap)

#if __INTEL__

#define _Align(type, mask) (sizeof(type) + (mask) & ~(mask))
#define va_arg(ap, type)	(* (type *) (((ap) += _Align(type, 3)) - _Align(type, 3)))

#elif	__POWERPC__ && (__dest_os	==	__mac_os)  /*for PowerMac 32bit calling conventions only*/

#define va_arg(ap, type)  (*       (((type *) (ap += (((sizeof(type)+3)/4)*4) )) -1)        )

#else

#define va_arg(ap, type)	(*       (((type *) (ap += sizeof(type))) - 1)        )

#endif

#if __INTEL__
#pragma pack(pop)
#endif

__end_namespace(stdc_space(stdarg))

__import_stdc_into_std_space(stdarg)

#endif /* __cstdarg__ */
/*     Change record
961015	bkoz	change to va_arg according to BR ES56366 (J. Pratt)
*/
