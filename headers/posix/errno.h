/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	errno.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __cerrno__
#define __cerrno__

#include <ansi_parms.h>

#if (__dest_os	== __win32_os)
#include <ThreadLocalData.h>
#endif

#if __dest_os == __be_os
				/* mm 970708 begin */

#include <Errors.h>

#define ENOERR          0
#define EOK 			ENOERR  /* some code assumes EOK exists */

extern

#if __cplusplus
"C"
#endif /* __cplusplus */

_IMPEXP_ROOT int *_errnop(void);	/* Be-mani 980107 */


#define errno (*(_errnop()))
				/* mm 970708 end */

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
# if __dest_os == __be_os		/* Be-mani 980107 needed for BeOS */
#  define ENOMEM					37             /* mm 970416*/
#  define EACCES					38             /* mm 970416*/
#  define ENOENT					39             /* mm 970416*/
#  define ENOSYS					40             /* mm 970416*/
# endif /* __dest_os */

#endif

#if (__dest_os	== __win32_os)
	/*
	 * These are other error types defined in Visual C++.
	 * I'm not sure if these numbers will work properly with the constants
	 * defined above.
	 */
	#define EPERM				1
	#define EACCES				2
	#define EBADF				3
	#define EDEADLOCK			4
	#define EMFILE				5
	#define ENOENT				6
	#define ENFILE				7
	#define ENOSPC				8
	#define EINVAL				9
	#define EIO				   10
	#define ENOMEM			   11
	#define ENOSYS			   12
#endif

#if __dest_os != __be_os          /* mm 970708 */
__namespace(__stdc_space(errno))

__extern_c	/* 961217 KO */

/* 961219 KO */
#if (__dest_os	== __win32_os)
	#define errno (_GetThreadLocalData()->errno)	
#else
	__tls extern int errno;
#endif


__end_extern_c	/* 961217 KO */

__end_namespace(stdc_space(errno))

__import_stdc_into_std_space(errno)
#endif                         /* mm 970708 */


#endif /* __cerrno__ */

/*     Change record
 * 960829 bkoz added error info for x86, powerTV
 * 960930 mm   changed C++ comments to C comments for ANSI strict
 * 961217 KO	Added an extern C wrapper to errno. This is needed for the new CW11 x86
			name mangling.
 * 961219 KO	Added a Win32 ifdef so errno is part of the thread local data structure
         	rather than a global.
 * 970416 mm   Removed errors that no longer apply
 * mm 970708  Inserted Be changes
 * 980107 Be-mani	Merged Be changes
 */
