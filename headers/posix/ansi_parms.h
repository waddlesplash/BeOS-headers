/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	ansi_parms.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __ansi_parms__
#define __ansi_parms__

#define	__MODENALIB__	/*soon to be obsolete...*/	
#define __MSL__		22	/*  971015 vss  */	

/*	970402 bkoz 
	long long only supported on MIPS/PPC/68K CW11 tools and older
	and is on by default 
*/
#if __MC68K__ || __POWERPC__  || (__MOTO__ >= 30903)  || __INTEL__ 
	#define __MSL_LONGLONG_SUPPORT__				 /* mm 970110 */		
#endif

/*	970415 bkoz 
	define this if you would like FPCE functionality in math.h 
*/
/* #define __MSL_C9X__ */

#ifdef __cplusplus

#define __extern_c								extern "C" {
#define __end_extern_c						}

#define __std(ref)								/*std::*/ref

#define __namespace(space)				//namespace space {
#define __end_namespace(space)		//}

#define	__using_namespace(space)	//using namespace space;

#define __stdc_space(space)				//__c ## space ## _space

#define __import_stdc_into_std_space(space)	//	\
	__namespace(std)															\
		__using_namespace(__stdc_space(space))			\
	__end_namespace(std)

#else

#define __extern_c
#define __end_extern_c

#define __std(ref)								ref

#define __namespace(space)
#define __end_namespace(space)

#define	__using_namespace(space)

#define __stdc_space(space)

#define __import_stdc_into_std_space(space)

#endif /* __cplusplus */

#define __undef_os		0
#define __mac_os		1
#define __be_os			2
#define __win32_os		3
#define __powertv_os	4

#if !defined(__dest_os)               				/*MW-jcm 971114 */
#if	defined(__BEOS__)								/*MW-jcm 971114 */
#include <ansi_prefix.be.h>							/*MW-jcm 971114 */
#endif												/*MW-jcm 971114 */
 /* #define __dest_os __mac_os        */            /*MW-jcm 971114 */
#endif                                             /*MW-jcm 971114 */


#if	__dest_os	== __win32_os
#define	__tls	 __declspec(thread)
#define __LITTLE_ENDIAN
#else
#define	__tls 
#endif

#if __dest_os == __be_os		/* 980107 Be-mani */
# if __INTEL__					/* 980107 Be-mani */
#  define __LITTLE_ENDIAN 1		/* 980107 Be-mani */
# endif /* __INTEL__ */			/* 980107 Be-mani */
# include <BeBuild.h>			/* 980107 Be-mani */
#else							/* 980107 Be-mani */
# ifndef _IMPEXP_ROOT			/* 980107 Be-mani */
#  define	_IMPEXP_ROOT		/* 980107 Be-mani */
# endif							/* 980107 Be-mani */
#endif							/* 980107 Be-mani */

#endif /* __ansi_parms__ */

/*     Change record
 *  971015 vss  New version 2.2
 *	971114 jcm	added #if macintosh && !defined(__dest_os)
 * 	980107 Be-mani	Added LITTLE_ENDIAN def for BeOS/Intel
 *			Add Be shared library defs.
*/
