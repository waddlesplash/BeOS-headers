/*
 *	signal.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */

#ifndef __signal__
#define __signal__

#include <ansi_parms.h>

typedef int	sig_atomic_t;

#define SIG_DFL	((__signal_func_ptr)  0)
#define SIG_IGN	((__signal_func_ptr)  1)
#define SIG_ERR	((__signal_func_ptr) -1)

#define SIGABRT		1
#define SIGFPE		2
#define SIGILL		3
#define SIGINT		4
#define SIGSEGV		5
#define SIGTERM		6
#define	SIGHUP		7
#define SIGQUIT		8
#define SIGPIPE		9

#define __signal_max	9

typedef void (* __signal_func_ptr)(int);

__extern_c

__signal_func_ptr	signal(int  signal, __signal_func_ptr signal_func);
int								raise (int  signal);

__end_extern_c

#endif /* __signal__ */
