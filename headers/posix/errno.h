/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	errno.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __cerrno__
#define __cerrno__

#include <ansi_parms.h>

#if __dest_os == __be_os

#include <Errors.h>

#define ENOERR          0
#define EOK 			ENOERR  /* some code assumes EOK exists */

extern

#if __cplusplus
"C"
#endif /* __cplusplus */

int *_errnop(void);

extern int *_errnop(void);


#define errno (*(_errnop()))

#elif __dest_os == __powertv_os

	#define ENOERR					0
	#define EFPOS						1035		/* MSL error*/
	#define	ESIGPARM				1036		/* MSL error*/
	#include <errno.powertv.h>

#else

	#define ENOERR					 0
	#define EDOM						33
	#define ERANGE					34
	#define EFPOS						35
	#define	ESIGPARM				36
	#define ENOMEM					37
	#define EACCES					38
	#define ENOENT					39
	#define ENOSYS					40

#endif

#if (__dest_os	== __win32_os)
	/*
	 * These are other error types defined in Visual C++.
	 * I'm not sure if these numbers will work properly with the constants
	 * defined above.
	 */
	#define EPERM					1
	/*#define EACCES			2*/
	#define EBADF					3
	#define EDEADLOCK			4
	#define EMFILE				5
	/*#define ENOENT			6*/
	#define ENFILE				7
	#define ENOSPC				8
	#define EINVAL				9
	#define EIO						10
	/*#define ENOMEM			11*/
	/*#define ENOSYS			12*/
#endif

#if __dest_os != __be_os
__namespace(__stdc_space(errno))

__tls extern int errno;

__end_namespace(stdc_space(errno))

__import_stdc_into_std_space(errno)
#endif


#endif /* __cerrno__ */

/*     Change record
960829 bkoz added error info for x86, powerTV
960930 mm   changed C++ comments to C comments for ANSI strict
*/
