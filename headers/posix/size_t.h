/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	size_t.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __size_t__
#define __size_t__

#include <ansi_parms.h>			/* To get __dest_os */

#if __dest_os == __win32_os
	#define _SIZE_T_DEFINED
	typedef unsigned int	size_t;
#else
	typedef unsigned long	size_t;
	typedef long			ssize_t;
#endif

#endif /* __size_t__ */
/*     Change record
*/
