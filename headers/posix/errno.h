/*
 *	errno.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __errno__
#define __errno__

#define ENOERR          0

#define E2BIG           1
#define EACCES          2
#define EAGAIN          3
#define EBADF           4
#define EBUSY           5
#define ECHILD          6
#define EDEADLK         7
#define EEXIST          8
#define EFAULT          9
#define EFBIG           10
#define EINTR           11
#define EINVAL          12
#define	EIO             13
#define	EISDIR          14
#define	EMFILE          15
#define	EMLINK          16
#define ENAMETOOLONG	17
#define	ENFILE          18
#define ENODEV          19
#define	ENOENT          20
#define	ENOEXEC         21
#define ENOLCK          22
#define	ENOMEM          23
#define	ENOSPC          24
#define ENOSYS          25
#define	ENOTDIR	        26
#define ENOTEMPTY       27
#define ENOTTY          28
#define	ENXIO           29
#define	EPERM           30
#define	EPIPE           31
#define EROFS           32
#define ESPIPE          33
#define ESRCH           34
#define	EXDEV           35

#define EFPOS           36
#define	ESIGPARM        37

#define EDOM            38
#define ERANGE          39

#define _NERR	(ERANGE+1)  /* one more than last code */

extern int errno;

#endif /* __errno__ */
