/*
 *   locale.h -- ANSI 
 *
 *   Functions, types, and macros pertaining to geographic
 *   localization of numeric formats.
 *
 *           Copyright (c) 1990, MetaWare Incorporated
 */

#ifndef _LOCALE_H
#define _LOCALE_H
#pragma push_align_members(64);

#ifdef __CPLUSPLUS__
extern "C" {
#endif

struct lconv {
	char *decimal_point;
	char *thousands_sep;
	char *grouping;
	char *int_curr_symbol;
	char *currency_symbol;
	char *mon_decimal_point;
	char *mon_thousands_sep;
	char *mon_grouping;
	char *positive_sign;
	char *negative_sign;
	char int_frac_digits;
	char frac_digits;
	char p_cs_precedes;
	char p_sep_by_space;
	char n_cs_precedes;
	char n_sep_by_space;
	char p_sign_posn;
	char n_sign_posn;
};

#ifndef NULL
#define NULL            ((void *)0)
#endif

#if _ESA
#define LC_ALL	 	-1
#define LC_COLLATE	0
#define LC_CTYPE	1
#define LC_MONETARY	2
#define LC_NUMERIC	3
#define LC_TIME		4
#define LC_MESSAGES	5
#else
#define LC_ALL	 	1
#define LC_COLLATE	2
#define LC_CTYPE	3
#define LC_MONETARY	4
#define LC_NUMERIC	5
#define LC_TIME		6
#endif

extern char * setlocale(int __category, const char *__locale);
extern struct lconv *localeconv(void);

#ifdef __CPLUSPLUS__
}
#endif
#pragma pop_align_members();
#endif /*_LOCALE_H*/
