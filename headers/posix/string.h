/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	string.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __cstring__
#define __cstring__

#ifndef __ansi_parms__								/*MW-jcm 971114 */
#include <ansi_parms.h>								/*MW-jcm 971114 */
#endif												/*MW-jcm 971114 */

__namespace(__stdc_space(string))

#include <size_t.h>
#include <null.h>

/* #pragma options align=native */
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#if __dest_os == __be_os
	#include <bsd_mem.h>
	#include <string.be.h>               /* mm 970708 */
#endif

#define __max_errstr	32

__extern_c

_IMPEXP_ROOT void * 	memset(void * dst, int val, size_t len);
_IMPEXP_ROOT void * 	memchr(const void * src, int val, size_t len);
_IMPEXP_ROOT int		memcmp(const void * src1, const void * src2, size_t len);

__end_extern_c

#if !__MC68K__ || _No_BlockMove || __dest_os != __mac_os

	__extern_c
	
_IMPEXP_ROOT	void * memcpy (void * dst, const void * src, size_t len);
_IMPEXP_ROOT	void * memmove(void * dst, const void * src, size_t len);
	
	__end_extern_c

#else /* __MC68K__ && !_No_BlockMove && __dest_os == __mac_os */

	__extern_c
	
	void * __memcpy(void * : __A1, const void * : __A0, size_t : __D0) : __A1
		= {
				0x7220,			/*			moveq		#32, d1			*/
				0xB081,			/*			cmp.l		d1, d0			*/
				0x6504,			/*			bcs.s		@1				*/
				0xA22E,			/*			_BlockMoveData				*/
				0x600E,			/*			bra.s		@3				*/
				0x4A80,			/* @1:	tst.l		d0					*/
				0x670A,			/*			beq.s		@3				*/
				0x2209,			/* 			move.l	a1, d1				*/
				0x12D8,			/* @2:	move.b	(a0)+, (a1)+			*/
				0x5380,			/*			subq.l	#1, d0				*/
				0x66FA,			/*			bne.s		@2				*/
				0x2241			/*			move.l	d1, a1				*/
			};					/* @3:									*/
	
	void * __memmove(void * : __A1, const void * : __A0, size_t : __D0) : __A1
		= {
				0xA22E			/* _BlockMoveData */
			};
	
	__end_extern_c
	
	#ifdef __cplusplus
	
		inline void * memcpy (void * dst, const void * src, size_t len)
			{ return __memcpy(dst, src, len); }
		
		inline void * memmove(void * dst, const void * src, size_t len)
			{ return __memmove(dst, src, len); }
	
	#else
	
		void * memcpy (void * dst, const void * src, size_t len);
		void * memmove(void * dst, const void * src, size_t len);
		
		#define memcpy(dst, src, len)		__memcpy(dst, src, len)
		#define memmove(dst, src, len)	__memmove(dst, src, len)
	
	#endif

#endif /* !__MC68K__ || _No_BlockMove */

#if !__MC68K__ || _No_String_Inlines

	__extern_c
	
_IMPEXP_ROOT	size_t strlen(const char * str);
_IMPEXP_ROOT	char * strcpy(char * dst, const char * src);
	
	__end_extern_c

#else /* !(!__MC68K__ || _No_String_Inlines) */

	__extern_c
	
	size_t __strlen(const char * : __A0) : __D0
		= {
				0x70FF,			/*		moveq		-1, d0	*/
				0x5280,			/* @1	addq.l	#1, d0	*/
				0x4A18,			/*		tst.b		(a0)+		*/
				0x66FA			/*		bne.s		@1			*/
			};
		
	char * __strcpy(char * : __A0, const char * : __A1) : __D0 
		= {
				0x2008,			/*		move.l	a0, d0				*/
				0x10D9,			/* @1	move.b	(a1)+, (a0)+	*/
				0x66FC			/*		bne.s		@1						*/
			};
	
	__end_extern_c
	
	#ifdef __cplusplus
	
		inline size_t strlen(const char * str)
			{ return __strlen(str); }
		
		inline char * strcpy(char * dst, const char * src)
			{ return __strcpy(dst, src); }
	
	#else
	
		size_t strlen(const char * str);
		char * strcpy(char * dst, const char * src);
		
		#define strlen(str)				__strlen(str)
		#define strcpy(dst, src)	__strcpy(dst, src)
	
	#endif

#endif /* !__MC68K__ || _No_String_Inlines */

__extern_c

_IMPEXP_ROOT char * strncpy(char * dst, const char * src, size_t len);

_IMPEXP_ROOT char * strcat (char * dst, const char * src);
_IMPEXP_ROOT char * strncat(char * dst, const char * src, size_t len);

_IMPEXP_ROOT int    strcmp (const char * str1, const char * str2);
_IMPEXP_ROOT int    strncmp(const char * str1, const char * str2, size_t len);

_IMPEXP_ROOT int    strcoll(const char * str1, const char * str2);
_IMPEXP_ROOT size_t strxfrm(      char * str1, const char * str2, size_t len);

_IMPEXP_ROOT char * strchr (const char * str, int chr);
_IMPEXP_ROOT char * strrchr(const char * str, int chr);
_IMPEXP_ROOT char * strpbrk(const char * str, const char * set);
_IMPEXP_ROOT size_t strspn (const char * str, const char * set);
_IMPEXP_ROOT size_t strcspn(const char * str, const char * set);
_IMPEXP_ROOT char * strtok (      char * str, const char * set);

_IMPEXP_ROOT char * strstr(const char * str, const char * pat);

_IMPEXP_ROOT char * strerror(int errnum);

_IMPEXP_ROOT char * __strerror(int errnum, char * str);

_IMPEXP_ROOT void * __memrchr(const void * src, int val, size_t n);

#if (__dest_os == __be_os) || (__dest_os == __powertv_os)

/* prototypes for some useful but non-standard string routines */

_IMPEXP_ROOT int			strcasecmp (const char *str1, const char *str2);
_IMPEXP_ROOT int			strncasecmp(const char *str1, const char *str2, size_t nchars);	/* Be-mani 980107b */

_IMPEXP_ROOT char *	strdup(const char *str);
_IMPEXP_ROOT char *	stpcpy(char *dest, const char *src);     /* mm 970708 */

#endif
#if (__dest_os	== __win32_os)
	/* This #ifdef block contains declarations found in the corresponding */
	/* Visual C++ ANSI header.		*/

	/* These functions are defined in extras.c */
	int _stricmp(const char *s1, const char *s2);
	int _strnicmp(const char *s1, const char *s2, int n);
	char * _strrev(char *str);
	char *_strdup(const char *str);
	char *_strupr(char *str);
	size_t wcslen(const wchar_t *);
	wchar_t *wcscpy(wchar_t *, const wchar_t *);

#endif



__end_extern_c

__end_namespace(stdc_space(string))

__import_stdc_into_std_space(string)

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
/* #pragma options align=reset */

#endif

/*     Change record
 * MW-mm 960927a Inserted setting of __dest_os to __mac_os when not otherwise set.
 * mm 970708  Inserted Be changes
  * jcm 971114	wrapped the #include <ansi_parms.h>
 * jcm 971114	killed the macintosh defined && !defined (_dest_os) since it is in ansi_parms.h
 * Be-mani 980107 Added _IMPEXP_ROOT for BeOS shared libs.
 * Be-mani 980107b Changed prototype for strncasecmp.
 */

