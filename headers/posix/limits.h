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


#include <ansi_parms.h>    /* to pick up __dest_os */
#if __dest_os == __be_os

#define ARG_MAX             (128*1024)
#define CHILD_MAX	        (666)
#define LINK_MAX            (1)
#define MAX_CANON           (255)
#define MAX_INPUT           (255)
#define NAME_MAX            (64)
#define NGROUPS_MAX         (32)
#define OPEN_MAX            (32)
#define PATH_MAX            (1024)  /* really it's infinite though */
#define PIPE_MAX            (512)
#define SSIZE_MAX           (32767)
#define TZNAME_MAX          (32)

#define _POSIX_ARG_MAX      ARG_MAX
#define _POSIX_CHILD_MAX    CHILD_MAX
#define _POSIX_LINK_MAX     LINK_MAX
#define _POSIX_MAX_CANON    MAX_CANON
#define _POSIX_MAX_INPUT    MAX_INPUT
#define _POSIX_NAME_MAX     NAME_MAX
#define _POSIX_NGROUPS_MAX  NGROUPS_MAX
#define _POSIX_OPEN_MAX     OPEN_MAX
#define _POSIX_PATH_MAX     PATH_MAX
#define _POSIX_PIPE_MAX     PIPE_MAX
#define _POSIX_SSIZE_MAX    SSIZE_MAX
#define _POSIX_TZNAME_MAX   TZNAME_MAX

#endif /* __be_os */

#endif /* __limits__ */
