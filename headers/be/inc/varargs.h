/* This file is to allow the flexibility of using old-style "varargs". */

#include <stdarg.h>

/* Undefine the ANSI va_start, and define a va_start in the format
 * expected by the old usage.
 */
#undef va_start
#define va_alist _va_alist, ...
#define va_dcl int _va_alist;

/* Redine va_start to call the High C-defined __va_start, and then
 * adjust the ap to back up to the beginning of the _va_alist parm.
 */
#if _I860
    #ifdef __TO_WORDS	/* MetaWare's stdarg.h. */
    #define va_start(ap) {__va_start(ap,_va_alist); ap.ireg_bytes -= sizeof(int) __TO_WORDS;}
    #else		/* AT&T's V.4 stdarg.h. */
    #define va_start(ap) {__va_start(ap,_va_alist); ap.ireg_used -= 1;}
    #endif
#elif _UPA
    #define va_start(ap) __builtin_va_start(ap,&_va_alist)
#else
#  define va_start(ap) {__va_start(ap,_va_alist); *(char**)&ap -= sizeof(int); }
#endif


