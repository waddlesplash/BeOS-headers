/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	size_t.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __size_t__
#define __size_t__

#include <ansi_parms.h>                 /* mm 970905*/

#if __dest_os == __win32_os || __MOTO__
	#define _SIZE_T_DEFINED
	typedef unsigned int	size_t;
#else
	typedef unsigned long	size_t;
#if __dest_os == __be_os				
	typedef long ssize_t;
#endif
#endif

#endif /* __size_t__ */

/*     Change record
 * mm 970905  added include of ansi_parms.h to avoid need for prefix file
 */
