/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	wchar_t.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __wchar_t__
#define __wchar_t__

#include <ansi_parms.h>                 /* mm 970905*/

	#if __dest_os == __win32_os
		#define _WCHAR_T_DEFINED
		typedef unsigned short wchar_t;
	#else
	    #if __MWERKS__ >= 0x2000  /* 971001 vss 2.0 compiler support for wchar_t */
	    typedef unsigned short wchar_t;
	    #else
		/*typedef unsigned char	wchar_t; */
		typedef  char	wchar_t; /*bkoz 960610 to fix c210421 test++ */
		#endif /* __MWERKS__ == 0x2000  */
	#endif

#endif /* __wchar_t__ */

/* change log
 * MW -bkoz 960829 hack until Andreas uses a 2byte format
 * mm 970905  added include of ansi_parms.h to avoid need for prefix file
 * 971001 vss  2.0 compiler for Mac now supports wchar_t as 2-byte character
 */
