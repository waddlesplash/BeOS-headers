/*
 * Copyright (c) 1993 MetaWare, Incorporated
 *
 * $Id: _na.h,v 1.1 1994/08/19 17:51:05 ming Exp $
 *
 */

#ifndef _NA_H
#define _NA_H

/* include _MSDOS as soon as most people have a compiler that supports
   _Typeof
*/
#if (__HIGHC__ && (/*_MSDOS ||*/ _MSNT || _OS2 || _HOBBIT ))
    #ifndef _NA_NAMES
	#define _NA_NAMES 1
    #endif
#endif

#define _NA(x) \
    extern _Typeof<_ ## x> x; _Pragma alias(x, _ ## x, _DEFAULT_UNDERSCORE_PREFIXING);

#if _SOL
    #ifndef _UID_T
    #define _UID_T
	typedef long    uid_t;
    #endif
    #if (__STDC__ - 0 == 0)
	/* Solaris 2 non ANSI compatible prototypes */
	extern long a64l(const char *);
	extern int dup2(int, int);
	extern char *ecvt(double, int, int *, int *);
	extern char *fcvt(double, int, int *, int *);
	extern char *qecvt(long double, int, int *, int *);
	extern char *qfcvt(long double, int, int *, int *);
	extern char *qgcvt(long double, int, char *);
	extern char *getcwd(char *, size_t);
	extern char *getlogin(void);
	extern int getopt(int, char *const *, const char *);
	extern int getsubopt(char **, char *const *, char **);
	extern char *optarg;
	extern int optind, opterr, optopt;
	extern char *getpass(const char *);
	extern int getpw(uid_t, char *);
	extern char *gcvt(double, int, char *);
	extern int isatty(int);
	extern char *l64a(long);
	extern void *memalign(size_t, size_t);
	extern char *mktemp(char *);
	extern int putenv(char *);
	extern char *realpath(char *, char *);
	extern void swab(const char *, char *, int);
	extern char *ttyname(int);
	extern int ttyslot(void);
	extern void *valloc(size_t);

	extern double drand48(void);
	extern double erand48(unsigned short *);
	extern long jrand48(unsigned short *);
	extern void lcong48(unsigned short *);
	extern long lrand48(void);
	extern long mrand48(void);
	extern long nrand48(unsigned short *);
	extern unsigned short *seed48(unsigned short *);
	extern void srand48(long);

	#if !defined(_NO_LONGLONG)
	    typedef struct {
		long long	quot;
		long long	rem;
	    } lldiv_t;

	    extern long long atoll(const char *);
	    extern long long llabs(long long);
	    extern lldiv_t lldiv(long long, long long);
	    extern char *lltostr(long long, char *);
	    extern long long strtoll(const char *, char **, int);
	    extern unsigned long long strtoull(const char *, char **, int);
	    extern char *ulltostr(unsigned long long, char *);
	#endif	/* !defined(_NO_LONGLONG) */
    #endif /* (__STDC__ - 0 == 0) */
#endif /* _SOL */


#endif
