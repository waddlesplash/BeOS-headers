/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	ansi_parms.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __ansi_parms__
#define __ansi_parms__

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


#if	__dest_os	== __win32_os
#define	__tls	 __declspec(thread)
#define __LITTLE_ENDIAN
#else
#define	__tls 
#endif

#define __dest_os	__be_os

#endif /* ndef __ansi_parms__ */

/*     Change record
*/
