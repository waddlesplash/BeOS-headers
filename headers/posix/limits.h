/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	limits.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __climits__
#define __climits__

#ifndef __ansi_parms__								/*MW-jcm 971114 */
#include <ansi_parms.h>                     		/* mm 970804 */
#endif												/*MW-jcm 971114 */

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

#if __fourbyteints__

	#define	INT_MIN			LONG_MIN
	#define INT_MAX			LONG_MAX
	#define UINT_MAX		ULONG_MAX

#else

	#define	INT_MIN			SHRT_MIN
	#define INT_MAX			SHRT_MAX
	#define UINT_MAX		USHRT_MAX
	
#endif /* __fourbyteints__ */

#ifdef	__MSL_LONGLONG_SUPPORT__
/*	970216 bkoz want this
    #define LONGLONG_MIN   (-9223372036854775807LL - 1)
	#define LONGLONG_MAX     9223372036854775807LL
	#define ULONGLONG_MAX   18446744073709551615ULL
*/
	#define LONGLONG_MIN    (-9223372036854775807 - 1)
	#define LONGLONG_MAX     9223372036854775807
	#define ULONGLONG_MAX     0xffffffffffffffff

#else
	#define LONGLONG_MIN    	LONG_MIN
	#define LONGLONG_MAX     	LONG_MAX
	#define ULONGLONG_MAX     	ULONG_MAX
#endif


#if __dest_os == __be_os
	#include <limits.be.h>
#endif

#endif /* __climits__ */
/*     Change record
961216 bkoz line 49 added long long typedefs
970214 bkoz added default __dest_os __mac_os
* mm 970804 Added include of ansi_parms.h to ensure __mac_os, __be_os, etc are defined.
* jcm 971114	wrapped and added the #include <ansi_parms.h>
* jcm 971114	killed the macintosh defined && !defined (_dest_os) since it is in ansi_parms.h
 */
