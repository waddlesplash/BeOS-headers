/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	time.h
 *
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */

#ifndef __ctime__
#define __ctime__

#include <ansi_parms.h>

__namespace(__stdc_space(time))

#include <null.h>
#include <size_t.h>

#if macintosh && !defined(__dest_os)               /*MW-mm 960927a*/
  #define __dest_os __mac_os                       /*MW-mm 960927a*/
#endif                                             /*MW-mm 960927a*/

/*
 *		In order for __dest_os to be defined, the appropriate file
 *		<ansi_prefix.*.h> must be #included before this file, if you
 *		are on a mac and __dest_os is not defined __mac_os is set.
 *		__dest_os is needed to determine the correct value for
 *		CLOCKS_PER_SEC below.
 */


#if __dest_os == __mac_os

#define CLOCKS_PER_SEC	60

typedef unsigned long	clock_t;

#elif __dest_os == __be_os

#define CLOCKS_PER_SEC	1000
#define CLK_TCK         CLOCKS_PER_SEC

#ifndef _CLOCK_T_DEFINED_

typedef long	clock_t;

#define _CLOCK_T_DEFINED_
#endif /* _CLOCK_T_DEFINED_ */

__extern_c

void tzset(void);

extern char *tzname[2];

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
	#if __dest_os == __win32_os
		typedef long time_t;
	#else
		typedef long	time_t;
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
	int tm_gmtoff;
	char *tm_zone;
};

__extern_c

clock_t			clock(void);
double			difftime(time_t time1, time_t time2);
time_t			mktime(struct tm * timeptr);
time_t			time(time_t * timer);
char *			asctime(const struct tm * timeptr);
char *			ctime(const time_t * timer);
struct tm *		gmtime(const time_t * timer);
struct tm *		localtime(const time_t * timer);
size_t			strftime(char * s, size_t maxsize,
						 const char *format, const struct tm * timeptr);

clock_t	__get_clock(void);
time_t	__get_time(void);

#if __dest_os == __be_os

extern char *	tzname[2];
extern int 				daylight;
extern long 			timezone;
int				stime(time_t *t);
void			tzset(void);

#endif /* __be_os */

#if (__dest_os	== __win32_os)

	/* This #ifdef block contains declarations found in the corresponding */
	/* Visual C++ ANSI header.		*/
	/* This function is defined in extras.c */
	char *_strdate(char *str);

#endif


__end_extern_c

__end_namespace(stdc_space(time))

__import_stdc_into_std_space(time)

#pragma options align=reset

#endif

/*     Change record 
MW-mm 960927a Inserted setting of __dest_os to __mac_os when not otherwise set.
MW-mm 960927b Removed duplicate definition of time_t 
960912 KO     Made typedef for Win32 time_t in accord with Microsoft's definition
961011 KO     Made typedef for Win32 clock_t in accord with Microsoft's definition
*/
