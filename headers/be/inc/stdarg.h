/*
 *	stdarg.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __stdarg__
#define __stdarg__

#include <va_list.h>

#define __va_start(parm)	(va_list) (&parm + 1)

#define va_start(ap, parm)	ap = __va_start(parm)
#define va_arg(ap, type)		(* (((type *) (ap += sizeof(type))) - 1))
#define va_end(ap)

#endif /* __stdarg__ */
