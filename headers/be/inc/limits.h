/*
 *	limits.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __limits__
#define __limits__

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

#define LONG_MIN			(-2147483647-1)
#define LONG_MAX			  2147483647

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

#endif /* __limits__ */
