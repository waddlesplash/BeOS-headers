/*
 *   stdlib.h -- ANSI 
 *
 *   Functions, types, and macros that are of general utility.
 *
 *           Copyright (c) 1990, MetaWare Incorporated
 */

#ifndef _STDLIB_H
#define _STDLIB_H
#pragma push_align_members(64);

#ifdef __CPLUSPLUS__
extern "C" {
#endif

#ifndef _SIZET_H
#include <sizet.h>
#endif

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
typedef _wchar_t wchar_t;
#endif

#ifndef _DIV_T_DEFINED
#define _DIV_T_DEFINED
typedef struct { int quot; int rem; } div_t;
typedef struct { long quot; long rem; } ldiv_t;
#endif

#ifndef NULL
#define NULL            ((void *)0)
#endif

#define EXIT_FAILURE    1
#define EXIT_SUCCESS    0

#ifndef _UNICHAR_DEFINED
    typedef unsigned short _UNICHAR;
    #define _unichar _UNICHAR
    #define _UNICHAR_DEFINED
#endif


/* string conversion functions */
extern  double         atof(const char *__nptr);
extern  long double    _atold(const char *__nptr);
extern  int            atoi(const char *__nptr);
extern  long           atol(const char *__nptr);
extern  double         strtod(const char *__nptr, char **__endptr);
extern  long           strtol(const char *__nptr, char **__endptr, int __base);
extern  unsigned long  strtoul(const char *__nptr, char **__endptr, int __base);

extern void _swab(char *__from_ptr,char *__to_ptr,int __kount);
#include <_na.h>
#if _NA_NAMES
    _NA(swab)
#elif _MSDOS && __HIGHC__
    extern void swab(char *__from_ptr,char *__to_ptr,int __kount);
#endif


/* pseudo-random number generator */
#if _IBMESA || (_I860 && _ATT4)
    #define RAND_MAX 32767 	/* Match vendor's limited range. */
#else
    #define RAND_MAX (sizeof(int) == 2 ? 32767 : 2147483647)
#endif
#define MB_CUR_MAX      1

extern  int             rand(void);
extern  void            srand(unsigned int __seed);

/* memory management functions */

#ifdef DEBUG_ALLOC
extern  void *          debug_calloc(size_t __nelem, size_t __size, char *file, int line);
extern  void            debug_free(void *__ptr, char *file, int line);
extern  void *          debug_malloc(size_t __size, char *file, int line);
extern  void *          debug_realloc(void *__ptr, size_t __size, char *file, int line);

#define calloc(a,b) debug_calloc((a),(b),__FILE__,__LINE__);
#define free(a) debug_free((a), __FILE__, __LINE__);
#define malloc(a) debug_malloc((a), __FILE__, __LINE__);
#define realloc(a,b) debug_realloc((a),(b), __FILE__, __LINE__);

#else
extern  void *          calloc(size_t __nelem, size_t __size);
extern  void            free(void *__ptr);
extern  void *          malloc(size_t __size);
extern  void *          realloc(void *__ptr, size_t __size);
#endif

/* shared memory functions */
extern	void *		_smalloc(size_t __size);
extern  void            _sfree(void *__ptr);

/* communication with the environment */
extern  void            abort(void);
extern  int             atexit(void (*func)(void));
extern  void            exit(int __status);
extern  char *          getenv(const char *__name);
extern  int             system(const char *__string);

/* number-to-string conversion routines */
extern char * _itoa(int, char *, int);
extern char * _ltoa(long ,char *, int);
#if _HOBBIT
  #if __HIGHC__
    extern char * ultoa(unsigned long, char *, int);
  #endif
#else
    extern char * _ultoa(unsigned long, char *, int);
#endif
extern char * _utoa(unsigned int, char *, int);
extern char * _ecvt(double, int, int *, int *);
extern char * _fcvt(double, int, int *, int *);
extern char * _gcvt(double, int, char *);
#include <_na.h>
#if _NA_NAMES
    _NA(itoa)
    _NA(ltoa)
  #if !_HOBBIT
    _NA(ultoa)
  #endif
    _NA(utoa)
    _NA(ecvt)
    _NA(fcvt)
    _NA(gcvt)
#elif _MSDOS && __HIGHC__
    extern char * itoa(int, char *, int);
    extern char * ltoa(long ,char *, int);
    extern char * ultoa(unsigned long, char *, int);
    extern char * utoa(unsigned int, char *, int);
    extern char * ecvt(double, int, int *, int *);
    extern char * fcvt(double, int, int *, int *);
    extern char * gcvt(double, int, char *);
#endif

extern unsigned int _rotl(unsigned int ,int );
extern unsigned int _rotr(unsigned int ,int );
extern unsigned long _lrotl(unsigned long ,int );
extern unsigned long _lrotr(unsigned long ,int );
extern unsigned short _srotl(unsigned short ,int );
extern unsigned short _srotr(unsigned short ,int );
extern unsigned char _crotl(unsigned char ,int );
extern unsigned char _crotr(unsigned char ,int );


/* searching and sorting utilities */
extern  void *          bsearch(const void *__key, const void *__base,
                                size_t __nmemb, size_t __size,
                                int (*__compar)(const void *, const void *));
extern  void            qsort(void *__base, size_t __nmemb, size_t __size,
                                int (*__compar)(const void *, const void *));

/* integer arithmetic functions */
#undef abs
#undef labs
extern  int             abs(int __j);
extern  long            labs(long int __j);

extern  div_t           div(int __numer, int __denom);
extern  ldiv_t          ldiv(long int __numer, long int __denom);

/* Multibyte character functions */
extern  int		mblen(const char *__s, size_t __n);
#define mblen( s, n )   mbtowc((wchar_t *)0, s, n)
extern  int             mbtowc(wchar_t *__pwc, const char *__s, size_t __n);
extern  int             wctomb(char *__s, wchar_t __wchar);

/* Multibyte string functions */
extern  size_t          mbstowcs(wchar_t *__pwcs, const char *__s, size_t __n);
extern  size_t          wcstombs(char *__s, const wchar_t *__pwcs, size_t __n);


/* Unicode functions */
extern  double         	_uatof(const _unichar *__nptr);
extern  int           	_uatoi(const _unichar *__nptr);
extern  long           	_uatol(const _unichar *__nptr);

extern _unichar * 	_uitoa(int, _unichar *, int);
#if _HOBBIT
extern _unichar * 	_ultoa(long ,_unichar *, int);
#else
extern _unichar * 	_u_ltoa(long ,_unichar *, int);
#endif
extern _unichar * 	_uultoa(unsigned long, _unichar *, int);
extern _unichar * 	_uutoa(unsigned int, _unichar *, int);

extern  long           	_ustrtol(const _unichar *__nptr, _unichar **__endptr,
				int __base);
extern  double         	_ustrtod(const _unichar *__nptr, _unichar **__endptr);
extern  unsigned long  	_ustrtoul(const _unichar *__nptr, _unichar **__endptr,
				int __base);

extern _unichar * 	_uecvt(double, int, int *, int *);
extern _unichar * 	_ufcvt(double, int, int *, int *);
extern _unichar * 	_ugcvt(double, int, _unichar *);

extern _unichar *	_atouni(_unichar *, const char *);

#if __HIGHC__
  #ifdef __UNICODE__
    #define Uatof _uatof
    #define Uatoi _uatoi
    #define Uatol _uatol

    #define Uitoa  _uitoa
   #if _HOBBIT
    #define Ultoa  _ultoa
   #else
    #define Ultoa  _u_ltoa
   #endif
    #define Uultoa _uultoa
    #define Uutoa  _uutoa

    #define Ustrtol  _ustrtol
    #define Ustrtod  _ustrtod
    #define Ustrtoul _ustrtoul

    #define Uecvt _uecvt
    #define Ufcvt _ufcvt
    #define Ugcvt _ugcvt
  #else
    #define Uatof atof
    #define Uatoi atoi
    #define Uatol atol

    #define Uitoa  _itoa
    #define Ultoa  _ltoa
   #if _HOBBIT
    #define Uultoa ultoa
   #else
    #define Uultoa _ultoa
   #endif
    #define Uutoa  _utoa

    #define Ustrtol  strtol
    #define Ustrtod  strtod
    #define Ustrtoul strtoul

    #define Uecvt _ecvt
    #define Ufcvt _fcvt
    #define Ugcvt _gcvt
  #endif
#endif

/*---------------------------------------------------------------------
        Functionality limited to DOS, NT, OS2
*/

#if _MSDOS || _MSNT || _OS2
    extern char *_sys_errlist[];
    extern int _sys_nerr;
    #ifdef _REENTRANT
	#include <static.h>
    #else
	extern int  _doserrno;
    #endif
    #if !(defined(_REENTRANT) && _MSDOS)
	extern int _fmode;
	extern char ** _environ;
    #endif

    extern int _putenv(char *);
    extern void _exit(int __status);
    extern void _sleep(unsigned __seconds);

    #if _MSDOS
       #define _MAX_PATH 144
       #define _MAX_DRIVE 3
       #define _MAX_DIR 130
       #define _MAX_FNAME 9
       #define _MAX_EXT 5
    #else
       #define _MAX_PATH 260
       #define _MAX_DRIVE 3
       #define _MAX_DIR 256
       #define _MAX_FNAME 256
       #define _MAX_EXT 256
    #endif

    extern void _searchenv(char *,char *,char *);
    extern void _splitpath(char *,char *,char *,char *,char *);
    extern void _makepath(char *,char *,char *,char *,char *);
/*
 * Can't declare errno volatile. See
 * errno.h for information.
 */
    #include <_na.h>
    #if _NA_NAMES
	#ifndef _REENTRANT
	    extern int  errno;
	    _NA(environ)
	#endif
	_NA(putenv)
	_NA(sleep)
        extern void perror(const char *);
    #elif _MSDOS && __HIGHC__
	#ifndef _REENTRANT
	    extern int  errno;
	    extern char ** environ;
	    #pragma alias(environ,"_environ");
	#endif
        extern void perror(const char *);
	extern int  putenv(char *);
	extern void sleep(unsigned __seconds);
    #endif
#endif


#if _MSDOS
    extern unsigned char _osmajor;
    extern unsigned char _osminor;
    extern unsigned char _osmode;
    extern unsigned int _psp;

    #if __HIGHC__ 
	#ifndef tolower
	    extern int tolower(int __c);
	#endif
	#ifndef toupper
	    extern int toupper(int __c);
	#endif

	#define DOS_MODE 0
	#define OS2_MODE 1
    #endif /* __HIGHC__ */
#endif /* _MSDOS */


#ifdef __CPLUSPLUS__
}
#endif
#pragma pop_align_members();
#endif /*STDLIB_H*/
