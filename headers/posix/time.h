/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	time.h
 *
 *		Copyright � 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */

#ifndef __ctime__
#define __ctime__

#ifndef __ansi_parms__								/*MW-jcm 971114 */
#include <ansi_parms.h>								/*MW-jcm 971114 */
#endif												/*MW-jcm 971114 */

__namespace(__stdc_space(time))

#include <null.h>
#include <size_t.h>

/*
 *		In order for __dest_os to be defined, the appropriate file
 *		<ansi_prefix.*.h> must be #included before this file, if you
 *		are on a mac and __dest_os is not defined __mac_os is set.
 *		__dest_os is needed to determine the correct value for
 *		CLOCKS_PER_SEC below.
 */

/* #pragma options align=native */
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#if __dest_os == __mac_os

#define CLOCKS_PER_SEC	60

typedef unsigned long	clock_t;

#elif __dest_os == __be_os

#define CLOCKS_PER_SEC	1000               /* mm 970708 */
#define CLK_TCK         CLOCKS_PER_SEC

#ifndef _CLOCK_T_DEFINED_                  /* mm 970708 */

typedef long	clock_t;                   /* mm 970708 */

#define _CLOCK_T_DEFINED_                  /* mm 970708 */
#endif /* _CLOCK_T_DEFINED_ */             /* mm 970708 */

__extern_c

extern _IMPEXP_ROOT void tzset(void);

extern _IMPEXP_ROOT char *tzname[2];

__end_extern_c

#elif __dest_os == __win32_os
	#define CLOCKS_PER_SEC	1000
	#define CLK_TCK         CLOCKS_PER_SEC
	typedef long	clock_t;	/* 961011 KO */
#elif __dest_os == __powertv_os
	typedef unsigned long clock_t;
	#define CLOCKS_PER_SEC 1000000
#endif

/* 960912 KO: Put the Win32 stuff inside an ifdef block. Changed it to long
to match  Microsoft's definition of time_t.*/
#ifndef _TIME_T_DEFINED
	#if (__dest_os == __win32_os) || (__dest_os == __be_os)	/* Be-mani 980107 */
		typedef long time_t;
	#else
		typedef unsigned long	time_t;
	#endif
	#define _TIME_T_DEFINED 	/* avoid multiple def's of time_t */
#endif

struct tm {
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
#if __dest_os == __be_os		/* Be-mani 980107 */
	int tm_gmtoff;
	char *tm_zone;
#endif	
};

__extern_c

_IMPEXP_ROOT clock_t			clock(void);
_IMPEXP_ROOT double			difftime(time_t time1, time_t time2);
_IMPEXP_ROOT time_t			mktime(struct tm * timeptr);
_IMPEXP_ROOT time_t			time(time_t * timer);
_IMPEXP_ROOT char *			asctime(const struct tm * timeptr);
_IMPEXP_ROOT char *			ctime(const time_t * timer);
_IMPEXP_ROOT struct tm *		gmtime(const time_t * timer);
_IMPEXP_ROOT struct tm *		localtime(const time_t * timer);
_IMPEXP_ROOT size_t			strftime(char * s, size_t maxsize, const char * format, const struct tm * timeptr);

clock_t	__get_clock(void);
time_t	__get_time(void);
#if __dest_os != __be_os		/* Be-mani 980107 */
int		__to_gm_time(time_t * time);
#endif

#if (__dest_os == __be_os)		/* Be-mani 980107 */
/*
 * For BeOS timezone support
 */
extern _IMPEXP_ROOT int 	daylight;
extern _IMPEXP_ROOT long 	timezone;
extern _IMPEXP_ROOT int		stime(time_t *t);

#endif /* __dest_os */

#if (__dest_os	== __win32_os)

	/* This #ifdef block contains declarations found in the corresponding */
	/* Visual C++ ANSI header.		*/
	/* This function is defined in extras.c */
	char *_strdate(char *str);

#endif


__end_extern_c

__end_namespace(stdc_space(time))

__import_stdc_into_std_space(time)

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
/* #pragma options align=reset */

#endif

/*     Change record 
 * MW-mm 960927a Inserted setting of __dest_os to __mac_os when not otherwise set.
 * MW-mm 960927b Removed duplicate definition of time_t 
 * 960912 KO     Made typedef for Win32 time_t in accord with Microsoft's definition
 * 961011 KO     Made typedef for Win32 clock_t in accord with Microsoft's definition
 * mm 970708  Inserted Be changes
  * jcm 971114	wrapped the #include <ansi_parms.h>
 * jcm 971114	killed the macintosh defined && !defined (_dest_os) since it is in ansi_parms.h
 * Be-mani 980107 BeOS timezone support and shared lib changes.
 */
