/*
 *	time.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __time__
#define __time__

#include <ansi_parms.h>
#include <null.h>
#include <size_t.h>

#pragma options align=mac68k

#if __dest_os == __mac_os

#define CLOCKS_PER_SEC	60

typedef unsigned long	clock_t;

#elif __dest_os == __be_os

#define CLOCKS_PER_SEC	1000000

typedef double	clock_t;

#endif

typedef unsigned long	time_t;

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
};

__extern_c

clock_t			clock(void);
double			difftime(time_t time1, time_t time2);
time_t			mktime(struct tm * timeptr);
time_t			time(time_t * timer);
char *			asctime(const struct tm * timeptr);
char *			ctime(const time_t * timer);
struct tm *	gmtime(const time_t * timer);
struct tm *	localtime(const time_t * timer);
size_t			strftime(char * s, size_t maxsize, const char * format, const struct tm * timeptr);

clock_t	__get_clock(void);
time_t	__get_time(void);
int			__to_gm_time(time_t * time);

__end_extern_c

#pragma options align=reset

#endif
