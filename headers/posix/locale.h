/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	locale.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __clocale__
#define __clocale__

#include <ansi_parms.h>
#include <null.h>				/* 980107 Be-mani */

/* #pragma options align=native */
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

__namespace(__stdc_space(locale))

struct lconv {
	char	* decimal_point;
	char	* thousands_sep;
	char	* grouping;
	char	* int_curr_symbol;
	char	* currency_symbol;
	char	* mon_decimal_point;
	char	* mon_thousands_sep;
	char	* mon_grouping;
	char	* positive_sign;
	char	* negative_sign;
	char	  int_frac_digits;
	char	  frac_digits;
	char	  p_cs_precedes;
	char	  p_sep_by_space;
	char	  n_cs_precedes;
	char	  n_sep_by_space;
	char	  p_sign_posn;
	char	  n_sign_posn;
};

#define LC_FIRST		0

#define LC_ALL			0
#define LC_COLLATE	1
#define LC_CTYPE		2
#define LC_MONETARY	3
#define LC_NUMERIC	4
#define LC_TIME			5

#define LC_LAST			5

__extern_c

_IMPEXP_ROOT char		 *  setlocale(int category, const char *locale); /* Be-mani 980107 */
_IMPEXP_ROOT struct lconv * localeconv(void); /* Be-mani 980107 */

__end_extern_c

__end_namespace(stdc_space(locale))

__import_stdc_into_std_space(locale)

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
/* #pragma options align=reset */

#endif /* __clocale__ */
/*     Change record
 * 980107 Be-mani Merge in Be changes, shared libs etc.
*/
