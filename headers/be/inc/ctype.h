/*
 *   ctype.h -- ANSI 
 *
 *   Functions for handling characters.
 *
 *           Copyright (c) 1990, 1991, 1992, 1993 MetaWare Incorporated
 */

#ifndef	_CTYPE_H
#define	_CTYPE_H
#pragma push_align_members(64);

#ifdef __CPLUSPLUS__
extern "C" {
#endif

#define	_UPPER 1
#define	_LOWER 2
#define	_NUMBER	4
#define	_DIGIT	4
#define	_SPACE	8
#define	_PUNCT	16
#define	_CONTROL 32
#define	_CNTRL	32
#if _AIX || _ATT || _XNX || _ATT4 || _SOL || _MSNT
#define	_BLANK	64
#define	_HEX	128
#else
#define	_HEX	64
#define	_BLANK	128
#endif

#if _IBMESA || (_BSD && _I386 /* OSF/1 */)
    /* Structure info derived from localedef.h. */
    extern struct { 
    	char a,b; short c,d,e; void *f; 
    	struct { 
    	    short a,b,c,d,e,f; char g; int h; void *i; int j;
    	    unsigned short *lc_ctype;	/* At offset 28. */
    	    } *lc_chrtbl;
    	} *_locp;
    #define _CTYPE(c) ((_locp->lc_chrtbl->lc_ctype+1)[c])
#elif _AIX || _XNX || _ATT || _ATT4 || _SOL
    #if __ATTSTDC /* AT&T ANSI-std vs. non-ANSI std. ctype.	*/
	#define	_CTYPE(c)	((__ctype+1)[(c)])
 	extern const unsigned char __ctype[];
    #else
	#define	_CTYPE(c)	((_ctype+1)[(c)])
	extern const unsigned char _ctype[];
    #endif	/* __ATTSTDC */
#elif _MSNT
    #define	_CTYPE(c)	((_ctype+1)[(c)])
    extern const unsigned short _ctype[];
#elif _UPA
    #define _CTYPE(c)	(__ctype[(c)])
    extern unsigned char *__ctype;
#elif _I860BE
    #define	_CTYPE(c)	((__ctype+1)[(c)])
    extern const unsigned char __ctype[];
#else
    #define	_CTYPE(c)	((_ctype_+1)[(c)])
    extern const unsigned char _ctype_[];
#endif

/* put here for microsoft compatibility.  NT system headers depend on
   cytpe.h providing this.
*/
#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
typedef _wchar_t wchar_t;
#endif


extern	int	isupper(int __c);
extern	int	islower(int __c);
extern	int	isalpha(int __c);
extern	int	isdigit(int __c);
extern	int	isxdigit(int	__c);
extern	int	isspace(int __c);
extern	int	ispunct(int __c);
extern	int	isalnum(int __c);
extern	int	isgraph(int __c);
extern	int	isprint(int __c);
extern	int	iscntrl(int __c);
extern	int	toupper(int __c);
extern	int	tolower(int __c);
extern	int	_isascii(int	__c);
extern	int	_isodigit(int __c);
extern	int	_toupper(int	__c);
extern	int	_tolower(int	__c);

#define	isupper(c)	(_CTYPE(c) &	_UPPER)
#define	islower(c)	(_CTYPE(c) &	_LOWER)
#define	isalpha(c)	(_CTYPE(c) &	(_UPPER	| _LOWER))
#define	isdigit(c)	(_CTYPE(c) &	_NUMBER)
#define	isxdigit(c)	(_CTYPE(c) & 	(_NUMBER |	_HEX))
#define	isspace(c)	(_CTYPE(c) &	_SPACE)
#define	ispunct(c)	(_CTYPE(c) &	_PUNCT)
#define	isalnum(c)	(_CTYPE(c) &	(_UPPER|_LOWER|_NUMBER))
#define	isgraph(c)	(_CTYPE(c) &	(_UPPER	| _LOWER | _NUMBER | _PUNCT))
#define	isprint(c)	(_CTYPE(c) & 	(_UPPER |_LOWER |_NUMBER |_PUNCT |_BLANK))
#define	iscntrl(c)	(_CTYPE(c) &	_CNTRL)

#if __HIGHC__
#define	_toupper(c)	((c) - 'a' + 'A')
#define	_tolower(c)	((c) - 'A' + 'a')
#define	isascii(c)	((unsigned)(c) <= 0177)
#define	toascii(c)	((unsigned)(c) & 0177)
#endif

#ifdef _K_AND_R
#define	_isascii(c)	((unsigned)(c) <= 0177)
#define	isascii(c)	((unsigned)(c) <= 0177)
#define	toascii(c)	((unsigned)(c) & 0177)
#endif

#if _MSDOS
#define	_isodigit(c)	((unsigned int)(((c)&0xFF) - '0') <= 7)
#if __HIGHC__
#define	toupper(c)	(islower(c) ? _toupper(c) : (c))
#define	tolower(c)	(isupper(c) ? _tolower(c) : (c))
#endif
#endif

/* Unicode functions */

extern	int	_uisupper(int __c);
extern	int	_uislower(int __c);
extern	int	_uisalpha(int __c);
extern	int	_uisdigit(int __c);
extern	int	_uisxdigit(int	__c);
extern	int	_uisspace(int __c);
extern	int	_uispunct(int __c);
extern	int	_uisalnum(int __c);
extern	int	_uisgraph(int __c);
extern	int	_uisprint(int __c);
extern	int	_uiscntrl(int __c);
extern	int	_utoupper(int __c);
extern	int	_utolower(int __c);
extern	int	_uisascii(int	__c);
extern	int	_uisodigit(int __c);
extern	int	_utoupper(int	__c);
extern	int	_utolower(int	__c);

#if __HIGHC__
  #ifdef __UNICODE__
    #define Uisupper  _uisupper
    #define Uislower  _uislower
    #define Uisalpha  _uisalpha
    #define Uisdigit  _uisdigit
    #define Uisxdigit _uisxdigit
    #define Uisspace  _uisspace
    #define Uispunct  _uispunct
    #define Uisalnum  _uisalnum
    #define Uisgraph  _uisgraph
    #define Uisprint  _uisprint
    #define Uiscntrl  _uiscntrl
    #define Uisascii  _uisascii
    #define Uisodigit _uisodigit
    #define Utoupper  _utoupper
    #define Utolower  _utolower
  #else	/* ! __UNICODE__ */
    #define Uisupper  isupper
    #define Uislower  islower
    #define Uisalpha  isalpha
    #define Uisdigit  isdigit
    #define Uisxdigit isxdigit
    #define Uisspace  isspace
    #define Uispunct  ispunct
    #define Uisalnum  isalnum
    #define Uisgraph  isgraph
    #define Uisprint  isprint
    #define Uiscntrl  iscntrl
    #define Uisascii  _isascii
    #define Uisodigit _isodigit
    #define Utoupper  toupper
    #define Utolower  tolower
  #endif /* __UNICODE__ */
#endif /* __HIGHC__ */

#ifdef __CPLUSPLUS__
}
#endif
#pragma pop_align_members();
#endif /* _CTYPE_H */
