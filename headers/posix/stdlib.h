/*
 *	stdlib.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __stdlib__
#define __stdlib__

#pragma options align=mac68k

#include <ansi_parms.h>
#include <div_t.h>
#include <size_t.h>
#include <null.h>
#include <wchar_t.h>

#define RAND_MAX		32767
#define MB_CUR_MAX	    1

#define EXIT_SUCCESS		0
#define EXIT_FAILURE		1

__extern_c

double				atof(const char * str);
int						atoi(const char * str);
long					atol(const char * str);

double				strtod (const char * str, char ** end);
long					strtol (const char * str, char ** end, int base);
unsigned long	strtoul(const char * str, char ** end, int base);

int		rand (void);
void	srand(unsigned int seed);

void *	calloc(size_t nmemb, size_t size);
void		free(void *ptr);
void *	malloc(size_t size);
void *	realloc(void * ptr, size_t size);

void	abort(void);
int		atexit(void (*func)(void));
void	exit(int status);

char *	getenv(const char * name);
int			system(const char * command);

void *	bsearch(const void * key,
								const void * table_base, size_t num_members, size_t member_size,
								int (*compare_members)(const void *, const void *));

void		qsort(void * table_base, size_t num_members, size_t member_size,
							int (*compare_members)(const void *, const void *));

int		abs (int n);
div_t	div (int numerator, int denominator);

long		labs(long n);
ldiv_t	ldiv(long numerator, long denominator);

int			mblen(const char * s, size_t n);
int			mbtowc(wchar_t * pwc, const char * s, size_t n);
int			wctomb(char * s, wchar_t wchar);
size_t	mbstowcs(wchar_t * pwcs, const char * s, size_t n);
size_t	wcstombs(char * s, const wchar_t * pwcs, size_t n);

__end_extern_c

#pragma options align=reset

#endif /* __stdlib__ */
