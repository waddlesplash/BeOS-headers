/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	locale.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __clocale__
#define __clocale__


#include <ansi_parms.h>
#include <null.h>

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

char					* setlocale(int category, const char *locale);
struct lconv	* localeconv(void);

__end_extern_c

__end_namespace(stdc_space(locale))

__import_stdc_into_std_space(locale)

#pragma options align=reset

#endif /* __clocale__ */
/*     Change record
*/
