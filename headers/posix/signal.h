/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	signal.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */

#ifndef __csignal__
#define __csignal__

#include <ansi_parms.h>

/* #pragma options align=native */
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

__namespace(__stdc_space(signal))

typedef int	sig_atomic_t;

__extern_c

typedef void (* __signal_func_ptr)(int);

_IMPEXP_ROOT __signal_func_ptr	signal(int  signal, __signal_func_ptr signal_func);	/* Be-mani 980107 */
_IMPEXP_ROOT int								raise (int  signal); /* Be-mani 980107 */

__end_extern_c

#define SIG_DFL	((__std(__signal_func_ptr))  0)
#define SIG_IGN	((__std(__signal_func_ptr))  1)
#define SIG_ERR	((__std(__signal_func_ptr)) -1)

#if __dest_os == __be_os
# include <signal.be.h>
#else

	#define SIGABRT		1
	#define SIGFPE		2
	#define SIGILL		3
	#define SIGINT		4
	#define SIGSEGV		5
	#define SIGTERM		6
	
	#define __signal_max	6

#endif

__end_namespace(stdc_space(signal))

__import_stdc_into_std_space(signal)

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
/* #pragma options align=reset */

#endif /* __csignal__ */
/*     Change record
 * Be-mani 980107 Be shared lib changes.
*/
