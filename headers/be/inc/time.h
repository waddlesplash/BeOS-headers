/*
 *   time.h -- ANSI 
 *
 *   Functions, types, and a macro for manipulating
 *   representations of time.
 *
 *           Copyright (c) 1990, MetaWare Incorporated
 */

#ifndef	_TIME_H
#define	_TIME_H
#pragma push_align_members(64);

#ifdef __CPLUSPLUS__
extern "C" {
#endif

#ifndef	NULL
#define	NULL	  ((void *)0)
#endif

#ifndef _UNICHAR_DEFINED
    typedef unsigned short _UNICHAR;
    #define _unichar _UNICHAR
    #define _UNICHAR_DEFINED
#endif

#if _AIX || _SUN && !_SOL || _VAX
#   define CLOCKS_PER_SEC 60  /*Formerly CLK_TCK in previous ANSI drafts*/
#elif _ATT && _MC68		/*HP 9000	*/
#    define CLOCKS_PER_SEC 50	/*This may not be	true for all models!*/
#elif _MSDOS || _HOB
#   define CLOCKS_PER_SEC 100
#elif _ATT && _I386
#   define CLOCKS_PER_SEC 100
#elif (_ATT || _ATT4) && _I860
#   define CLOCKS_PER_SEC 100	/* Assumes clock_period=53330 in kernel.cfg. */
#elif (_NEXT)
#   define CLOCKS_PER_SEC 64
#elif _UPA || _SOL || _ATT4
#   define CLOCKS_PER_SEC 1000000
#else
#   define CLOCKS_PER_SEC 1000	/*Formerly CLK_TCK in previous ANSI drafts*/
#endif

#ifndef _SIZET_H
#include <sizet.h>
#endif

#if _IBMESA || _RS6000
typedef	     int	clock_t;
#elif (_I386 && _BSD)
typedef	     int	clock_t;
// Use the following line for gonzo (OSF 1 5.o)
// typedef	     unsigned int	clock_t;
#elif _UPA
typedef	unsigned long	clock_t;
#else
typedef	long int	clock_t;
#endif

#ifndef _TIME_T_DEFINED
#define _TIME_T_DEFINED
typedef	long int	time_t;
#endif

struct tm {
	int tm_sec;	/*seconds after	the minute- 0..59*/
	int tm_min;	/*minutes after	the hour- 0..59*/
	int tm_hour;	/*hours since midnight- 0..23*/
	int tm_mday;	/*day of the month-  1..31*/
	int tm_mon;	/*month of the year- 0..11*/
	int tm_year;	/*years since 1900*/
	int tm_wday;	/*days since Sunday-  0..6*/
	int tm_yday;	/*day of the year- 0..365*/
	int tm_isdst;	/*daylight savings time- boolean  (0,1,-1)*/
	};

/* Time	manipulation functions */
extern clock_t	clock(void);
extern double	difftime(time_t	__time1,time_t	__time0);
extern time_t	mktime(struct tm *__timeptr);
extern time_t	time(time_t *__timer);

/* Time	conversion functions */
extern char *	asctime(const	 struct	tm *__timeptr);
extern char *	ctime(const time_t *__timer);
extern struct tm * gmtime(const	time_t		*__timer);
extern struct tm * localtime(const time_t   *__timer);
extern size_t	strftime(char	 *__s, size_t	__maxsize,
			const  char *__format,	 const struct	tm *__timeptr);

extern struct tm *_localtime( const time_t *__timer, struct tm *__tmbuf );
extern char *_asctime( const struct tm *__timeptr, char *__buf );
extern char *_ctime( const time_t *__timer, char *__buf );
extern struct tm *_gmtime( const time_t *__timer, struct tm *__tmbuf );

extern char * _strdate(char *);
extern char * _strtime(char *);
extern void _tzset(void);

/* Unicode functions */
extern _unichar *_uasctime( const struct tm *__tmbuf );
extern _unichar *_uctime( const time_t *__timeval );
extern size_t    _ustrftime( _unichar *__s, size_t __maxsize,
        const _unichar *__format, const struct tm *__timeptr );
extern _unichar *_u_ctime( const time_t *__timeval, _unichar *__buf );
extern _unichar *_u_asctime( const struct tm *__tmbuf, _unichar *__buf );


#if !defined(_REENTRANT) || _HOBBIT || _MSNT || _OS2
    extern int _daylight;
    extern long _timezone;
    extern char *_tzname[2];
    extern _unichar *_utzname[2];

    extern long _timezone_std;
    extern long _timezone_dst;
#elif !defined(_STATIC_H)
    #include <static.h>
#endif

#define _TZNAME_MAX 32

#include <_na.h>
#if _NA_NAMES
    _NA(tzset)
    #if !defined(_REENTRANT) || _HOBBIT || _MSNT || _OS2
	_NA(daylight)
	_NA(timezone)
	_NA(tzname)
    #endif
#elif (_MSDOS || _HOBBIT) && __HIGHC__
    extern void tzset(void);
	/* Hobbit lib doesn't want timezone data in a thread-safe place */
    #if !defined(_REENTRANT) || _HOBBIT || _MSNT || _OS2
	extern int daylight;
	extern long timezone;
	extern char * tzname[2];
	#pragma alias(daylight,"_daylight");
	#pragma alias(timezone,"_timezone");
	#pragma alias(tzname,"_tzname");
    #endif
#endif /* __HIGHC__ */

#if __HIGHC__
    #ifdef __UNICODE__
	#define Uasctime  _uasctime
	#define Uctime    _uctime
	#define Ustrftime _ustrftime
	#define U_ctime   _u_ctime
	#define U_asctime _u_asctime
    #else
	#define Uasctime  asctime
	#define Uctime    ctime
	#define Ustrftime strftime
	#define U_ctime   _ctime
	#define U_asctime _asctime
    #endif
#endif

#ifdef __CPLUSPLUS__
}
#endif
#pragma pop_align_members();
#endif /*_TIME_H */
