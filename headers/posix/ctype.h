/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	ctype.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __cctype__
#define __cctype__


#include <ansi_parms.h>

__namespace(__stdc_space(ctype))

__extern_c

unsigned char	__ctype_map[];
unsigned char	__lower_map[];
unsigned char	__upper_map[];

__end_extern_c

#define __control_char	0x01
#define __motion_char		0x02
#define __space_char		0x04
#define __punctuation		0x08
#define __digit					0x10
#define __hex_digit			0x20
#define __lower_case		0x40
#define __upper_case		0x80

#define __letter				(__lower_case   | __upper_case  )
#define __alphanumeric	(__letter       | __digit       )
#define __graphic				(__alphanumeric | __punctuation )
#define __printable			(__graphic      | __space_char  )
#define __whitespace		(__motion_char  | __space_char  )
#define __control       (__motion_char  | __control_char)

#define __zero_fill(c)	((int) (unsigned char) (c))

#ifdef __cplusplus

inline int isalnum(int c)		{ return __ctype_map[__zero_fill(c)] & __alphanumeric; }
inline int isalpha(int c)		{ return __ctype_map[__zero_fill(c)] & __letter      ; }
inline int iscntrl(int c)		{ return __ctype_map[__zero_fill(c)] & __control     ; }
inline int isdigit(int c)		{ return __ctype_map[__zero_fill(c)] & __digit       ; }
inline int isgraph(int c)		{ return __ctype_map[__zero_fill(c)] & __graphic     ; }
inline int islower(int c)		{ return __ctype_map[__zero_fill(c)] & __lower_case  ; }
inline int isprint(int c)		{ return __ctype_map[__zero_fill(c)] & __printable   ; }
inline int ispunct(int c)		{ return __ctype_map[__zero_fill(c)] & __punctuation ; }
inline int isspace(int c)		{ return __ctype_map[__zero_fill(c)] & __whitespace  ; }
inline int isupper(int c)		{ return __ctype_map[__zero_fill(c)] & __upper_case  ; }
inline int isxdigit(int c)	{ return __ctype_map[__zero_fill(c)] & __hex_digit   ; }
inline int tolower(int c)		{ return __lower_map[__zero_fill(c)]; }
inline int toupper(int c)		{ return __upper_map[__zero_fill(c)]; }

#else

int isalnum (int);
int isalpha (int);
int iscntrl (int);
int isdigit (int);
int isgraph (int);
int islower (int);
int isprint (int);
int ispunct (int);
int isspace (int);
int isupper (int);
int isxdigit(int);
int tolower (int);
int toupper (int);

#define isalnum(c)	((int) (__ctype_map[__zero_fill(c)] & __alphanumeric))
#define isalpha(c)	((int) (__ctype_map[__zero_fill(c)] & __letter      ))
#define iscntrl(c)	((int) (__ctype_map[__zero_fill(c)] & __control     ))
#define isdigit(c)	((int) (__ctype_map[__zero_fill(c)] & __digit       ))
#define isgraph(c)	((int) (__ctype_map[__zero_fill(c)] & __graphic     ))
#define islower(c)	((int) (__ctype_map[__zero_fill(c)] & __lower_case  ))
#define isprint(c)	((int) (__ctype_map[__zero_fill(c)] & __printable   ))
#define ispunct(c)	((int) (__ctype_map[__zero_fill(c)] & __punctuation ))
#define isspace(c)	((int) (__ctype_map[__zero_fill(c)] & __whitespace  ))
#define isupper(c)	((int) (__ctype_map[__zero_fill(c)] & __upper_case  ))
#define isxdigit(c)	((int) (__ctype_map[__zero_fill(c)] & __hex_digit   ))
#define tolower(c)	((int)  __lower_map[__zero_fill(c)])
#define toupper(c)	((int)  __upper_map[__zero_fill(c)])

#endif

__end_namespace(__stdc_space(ctype))

__import_stdc_into_std_space(ctype)

#pragma options align=reset

#endif /* __cctype__ */
/*     Change record
*/
