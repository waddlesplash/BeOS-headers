/*
 *   stdarg.h -- ANSI 
 *
 *   Macros and type for functions that require variable
 *   numbers of arguments.
 *
 *           Copyright (c) 1990, 1993 MetaWare Incorporated
 */

#ifndef _STDARG_H
#define _STDARG_H	

#include <_stdarg.h>

#define va_start __va_start
#define va_arg   __va_arg
#define va_end   __va_end

typedef __va_list va_list;

#endif /*_STDARG_H*/
