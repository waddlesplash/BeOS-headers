/*
 *	errno.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __errno__
#define __errno__

#define ENOERR		 0
#define EDOM			33
#define ERANGE		34
#define EFPOS			35
#define	ESIGPARM	36
#define	EPERM			1
#define	ENOENT			2
#define	EINTR			4
#define	EIO				5
#define	ENXIO			6
#define	ENOEXEC			8
#define	EBADF			9
#define	ECHILD			10
#define	ENOMEM			12
#define	EACCES			13
#define	EBUSY			16
#define	EEXIST			17
#define	EXDEV			18
#define	ENOTDIR			20
#define	EISDIR			21
#define	EINVAL			22
#define	ENFILE			23
#define	EMFILE			24
#define	ENOSPC			28
#define	EPIPE			32
#define ENAMETOOLONG	78
#define _NERR	_ERRMAX	/* one more than last code */

extern int errno;

#endif /* __errno__ */
