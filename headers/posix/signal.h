/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	signal.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */

#ifndef __csignal__
#define __csignal__

#include <ansi_parms.h>

__namespace(__stdc_space(signal))

typedef int	sig_atomic_t;

__extern_c

typedef void (* __signal_func_ptr)(int);

__signal_func_ptr	signal(int  signal, __signal_func_ptr signal_func);
int								raise (int  signal);

__end_extern_c

#define SIG_DFL	((__std(__signal_func_ptr))  0)
#define SIG_IGN	((__std(__signal_func_ptr))  1)
#define SIG_ERR	((__std(__signal_func_ptr)) -1)

#if __dest_os == __be_os
	#include <signal.be.h>
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

#endif /* __csignal__ */
/*     Change record
*/
