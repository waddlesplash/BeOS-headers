/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	limits.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __climits__
#define __climits__

#define CHAR_BIT			8

#define SCHAR_MIN			(-127-1)
#define SCHAR_MAX			  127

#define	UCHAR_MAX			255U

#define CHAR_MIN			SCHAR_MIN
#define CHAR_MAX			SCHAR_MAX

#define MB_LEN_MAX		1

#define SHRT_MIN			(-32767-1)
#define SHRT_MAX			  32767

#define USHRT_MAX			65535U

#define LONG_MIN			(-2147483647L-1)
#define LONG_MAX			  2147483647L

#define ULONG_MAX			4294967295U

#define LONG_LONG_MIN			(-9223372036854775807LL-1)
#define LONG_LONG_MAX			  9223372036854775807LL

#define ULONG_LONG_MAX			18446744073709551615ULL  /* big! */

#if __fourbyteints__

	#define	INT_MIN			LONG_MIN
	#define INT_MAX			LONG_MAX
	#define UINT_MAX		ULONG_MAX

#else

	#define	INT_MIN			SHRT_MIN
	#define INT_MAX			SHRT_MAX
	#define UINT_MAX		USHRT_MAX
	
#endif /* __fourbyteints__ */

#include <ansi_parms.h>    /* to pick up __dest_os */
#if __dest_os == __be_os
	#include <limits.be.h>
#endif

#endif /* __climits__ */
/*     Change record
*/
