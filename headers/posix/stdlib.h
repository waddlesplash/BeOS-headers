/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	stdlib.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __cstdlib__
#define __cstdlib__

#include <ansi_parms.h>

__namespace(__stdc_space(stdlib))

#include <div_t.h>
#include <size_t.h>
#include <null.h>
#include <wchar_t.h>

/* #pragma options align=native */
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#define RAND_MAX		32767
#define MB_CUR_MAX	    1

#define EXIT_SUCCESS		0
#define EXIT_FAILURE		1

#if (__dest_os	!= __powertv_os)
#define _MAX_PATH				1024
#endif

__extern_c

_IMPEXP_ROOT double	atof(const char * str); /* Be-mani 980107, etc. */
_IMPEXP_ROOT int	atoi(const char * str); 
_IMPEXP_ROOT long	atol(const char * str); 

_IMPEXP_ROOT double	strtod (const char * str, char ** end); 
_IMPEXP_ROOT long	strtol (const char * str, char ** end, int base); 
_IMPEXP_ROOT unsigned long		strtoul(const char * str, char ** end, int base); 

#ifdef __MSL_LONGLONG_SUPPORT__               							/*mm 961219*/
_IMPEXP_ROOT long long			strtoll (const char * str, char ** end, int base);	/*mm 961219*/ 
_IMPEXP_ROOT unsigned long long	strtoull(const char * str, char ** end, int base);	/*mm 961219*/ 
#endif  /*__MSL_LONGLONG_SUPPORT__*/                      				/*mm 961220*/

_IMPEXP_ROOT int		rand (void); 
_IMPEXP_ROOT void	srand(unsigned int seed); 
#if __dest_os == __be_os               /* mm 970708 */
_IMPEXP_ROOT int		random (void);                 /* mm 970708 */ 
_IMPEXP_ROOT void	srandom(unsigned int seed);    /* mm 970708 */ 
_IMPEXP_ROOT char *		initstate(unsigned int seed, char *state, int n);
_IMPEXP_ROOT char *		setstate(char *state);
#endif                                 /* mm 970708 */

_IMPEXP_ROOT void *	calloc(size_t nmemb, size_t size); 
_IMPEXP_ROOT void	free(void *ptr); 
_IMPEXP_ROOT void *	malloc(size_t size); 
_IMPEXP_ROOT void *	realloc(void * ptr, size_t size); 

_IMPEXP_ROOT void	abort(void); 
_IMPEXP_ROOT int		atexit(void (*func)(void)); 
_IMPEXP_ROOT void	exit(int status); 

_IMPEXP_ROOT char *	getenv(const char * name); 
_IMPEXP_ROOT int		system(const char * command); 

#if __dest_os == __be_os               /* 980107b Be-mani */
_IMPEXP_ROOT int putenv(const char *string);
extern _IMPEXP_ROOT char ** environ;
_IMPEXP_ROOT int		atfork(void (*func)(void));
#endif /* dest_os == __be_os */

typedef int (*_compare_function)(const void*, const void*);                 /* mm 961031 */

_IMPEXP_ROOT void*	bsearch(const void*, const void*, size_t, size_t, _compare_function); /* mm 961031 */ 

_IMPEXP_ROOT void  qsort(void*, size_t, size_t, _compare_function);                      /* mm 961031 */ 
							
#if __POWERPC__

	#if __cplusplus && !__MOTO__ && !__MRC__
	
		inline int	abs (int n) { return(__abs(n)); }
		inline long	labs(long n){ return(__labs(n)); }
	
	#else
	
_IMPEXP_ROOT 		int		abs (int n); 
_IMPEXP_ROOT 		long	labs(long n); 
		
		#if !__MOTO__ && !__MRC__
		#define abs(n)	__abs(n)
		#define labs(n)	__labs(n)
		#endif
	
	#endif

#else

_IMPEXP_ROOT	int		abs (int n);
_IMPEXP_ROOT	long	labs(long n);

#endif

_IMPEXP_ROOT div_t		div (int numerator,  int denominator);
_IMPEXP_ROOT ldiv_t	ldiv(long numerator, long denominator);

_IMPEXP_ROOT int			mblen(const char * s, size_t n);
_IMPEXP_ROOT int			mbtowc(wchar_t * pwc, const char * s, size_t n);
_IMPEXP_ROOT int			wctomb(char * s, wchar_t wchar);
_IMPEXP_ROOT size_t	mbstowcs(wchar_t * pwcs, const char * s, size_t n);
_IMPEXP_ROOT size_t	wcstombs(char * s, const wchar_t * pwcs, size_t n);

#if (__dest_os	== __win32_os)

	/* This #ifdef block contains declarations found in the corresponding */
	/* Visual C++ ANSI header.		*/

	/* These functions are defined in extras.c */
	char * _fullpath(char * absPath, const char * relPath, size_t maxLength);
	char *_gcvt(double value, int digits, char *buffer);
	char * _itoa(int val, char *str, int radix);
	char * _ultoa(unsigned long val, char *str, int radix);
	#define _ltoa(x, y, z) _itoa(x, y, z)
	extern int _doserrno;
	#define _MAX_FNAME 256
#endif


__end_extern_c

__end_namespace(stdc_space(stdlib))

__import_stdc_into_std_space(stdlib)

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
/* #pragma options align=reset */

#endif /* __cstdlib__ */
/*     Change record
 * mm 961031  Improved legibility with introduction of typedef
 * mm 961220	line 44    Added headers for strtoll and strtoull for long long support
 * mm 970708  Inserted Be changes
 * Be-mani 980107 Inserted _IMPEXP_ROOT Be shared lib changes.
 * Be-mani 980107b Added environ and putenv.
 */
