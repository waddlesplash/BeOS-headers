/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	wchar_t.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __wchar_t__
#define __wchar_t__

#include <ansi_parms.h>			/* To get __dest_os */

#if __dest_os == __win32_os
		#define _WCHAR_T_DEFINED
		typedef unsigned short wchar_t;
	#else
		/*typedef unsigned char	wchar_t; */
		typedef  char	wchar_t; /*bkoz 960610 to fix c210421 test++ */
	#endif

#endif /* __wchar_t__ */

/* change log
MW -bkoz 960829 hack until Andreas uses a 2byte format
*/
