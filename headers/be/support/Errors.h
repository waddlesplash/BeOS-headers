/*

	Errors.h

    Copyright (c) 1994-96 by Be Incorporated.  All Rights Reserved.

*/

#ifndef _ERRORS_H
#define _ERRORS_H

#ifndef _LIMITS_H
#include <limits.h>
#endif

/* general errors */
#define B_GENERAL_ERROR_BASE		LONG_MIN
#define B_OS_ERROR_BASE				B_GENERAL_ERROR_BASE + 0x1000
#define B_APP_ERROR_BASE			B_GENERAL_ERROR_BASE + 0x2000
#define B_INTERFACE_ERROR_BASE		B_GENERAL_ERROR_BASE + 0x3000
#define B_MEDIA_ERROR_BASE			B_GENERAL_ERROR_BASE + 0x4000
#define B_MIDI_ERROR_BASE			B_GENERAL_ERROR_BASE + 0x5000
#define B_STORAGE_ERROR_BASE		B_GENERAL_ERROR_BASE + 0x6000
#define B_POSIX_ERROR_BASE			B_GENERAL_ERROR_BASE + 0x7000
#define B_MAIL_ERROR_BASE			B_GENERAL_ERROR_BASE + 0x8000
#define B_PRINT_ERROR_BASE			B_GENERAL_ERROR_BASE + 0x9000

/* end of be-defined error constants; dev-defined errors start here(+1) */
#define B_ERRORS_END		(B_GENERAL_ERROR_BASE + 0xffff)

/*
 * ---------------------------------------------------------------------------
			General Errors
 * ---------------------------------------------------------------------------
 */
enum {
	B_NO_MEMORY = B_GENERAL_ERROR_BASE,
								/* not enough memory to do something */
	B_IO_ERROR,					/* general io error */
	B_PERMISSION_DENIED,		/* probably just for files, but... */
	B_FILE_ERROR,				/* general file error */
	B_FILE_NOT_FOUND,			/* obvious */
	B_BAD_INDEX,				/* index not in range for the data set */
	B_BAD_TYPE,					/* bad argument type passed to function */
	B_BAD_VALUE,				/* bad argument value passed to function */
	B_MISMATCHED_VALUES,		/* conflicting arguments were passed */
	B_NAME_NOT_FOUND,			/* given name not found */
	B_NAME_IN_USE,				/* for named token creation functions */
	B_TIMED_OUT,				/* time-out limit expired */
    B_INTERRUPTED,              /* call was interrupted by a signal */
	B_WOULD_BLOCK,              /* call would have blocked */
    B_CANCELED,              	/* User did stop operation */

	B_ERROR = -1,				/* for the very lazy */
	B_OK = 0,
	B_NO_ERROR = 0
};

/*
 * ---------------------------------------------------------------------------
			OS Kit Errors
 * ---------------------------------------------------------------------------
 */
enum {
/* semaphore errors */
	B_BAD_SEM_ID = B_OS_ERROR_BASE,	/* operation request on an invalid semaphore */
	B_NO_MORE_SEMS,				/* all semaphore ids are taken */

/* thread errors */
	B_BAD_THREAD_ID = B_OS_ERROR_BASE + 0x100,
								/* operation on an invalid thread */
	B_NO_MORE_THREADS,			/* all thread ids are taken */
	B_BAD_THREAD_STATE,			/* thread in inappropriate state. */
	B_BAD_TEAM_ID,				/* operation on an invalid team */
	B_NO_MORE_TEAMS,			/* all team ids are taken */

/* message port errors */
	B_BAD_PORT_ID = B_OS_ERROR_BASE + 0x200,
								/* operation request on an invalid port */
	B_NO_MORE_PORTS,			/* all port ids are taken */

/* image errors */
	B_BAD_IMAGE_ID = B_OS_ERROR_BASE + 0x300,

/* debugger interface errors */
	B_DEBUGGER_ALREADY_INSTALLED = B_OS_ERROR_BASE + 0x400
								/* debugger already installed for this team */
};


/*
 * ---------------------------------------------------------------------------
			App Kit Errors
 * ---------------------------------------------------------------------------
 */
enum
{
/* message/messenger errors */
	B_BAD_REPLY = B_APP_ERROR_BASE,
								/* an invalid or unwanted reply */
	B_DUPLICATE_REPLY,			/* sending 1 replies to the same message */
	B_MESSAGE_TO_SELF,			/* can't send message to self (same pid) */
	B_BAD_HANDLER,
	B_ALREADY_RUNNING,
	B_LAUNCH_FAILED
};


/* Media Kit Errors */

enum {
  B_STREAM_NOT_FOUND = B_MEDIA_ERROR_BASE,
  B_SERVER_NOT_FOUND,
  B_RESOURCE_NOT_FOUND,
  B_RESOURCE_UNAVAILABLE,
  B_BAD_SUBSCRIBER,
  B_SUBSCRIBER_NOT_ENTERED,
  B_BUFFER_NOT_AVAILABLE,
  B_LAST_BUFFER_ERROR
};


/* 
 * Posix and Berkeley socket errors
 * These must be #define's and not enums
 */
#define E2BIG			(B_POSIX_ERROR_BASE + 1)
/* #define _ERROR_2		(B_POSIX_ERROR_BASE + 2)	reserved */
/* #define _ERROR_3		(B_POSIX_ERROR_BASE + 3)	reserved */
#define EBADF			(B_POSIX_ERROR_BASE + 4)
#define EBUSY			(B_POSIX_ERROR_BASE + 5)
#define ECHILD			(B_POSIX_ERROR_BASE + 6)
#define EDEADLK			(B_POSIX_ERROR_BASE + 7)
#define EEXIST			(B_POSIX_ERROR_BASE + 8)
#define EFAULT			(B_POSIX_ERROR_BASE + 9)
#define EFBIG			(B_POSIX_ERROR_BASE + 10)
/* #define _ERROR_11	(B_POSIX_ERROR_BASE + 11)	reserved */
#define EINVAL			(B_POSIX_ERROR_BASE + 12)
/* #define _ERROR_13	(B_POSIX_ERROR_BASE + 13) 	reserved */
#define EISDIR			(B_POSIX_ERROR_BASE + 14)
#define EMFILE			(B_POSIX_ERROR_BASE + 15)
#define EMLINK			(B_POSIX_ERROR_BASE + 16)
#define ENAMETOOLONG	(B_POSIX_ERROR_BASE + 17)
#define ENFILE			(B_POSIX_ERROR_BASE + 18)
#define ENODEV			(B_POSIX_ERROR_BASE + 19)
#define ENOENT			(B_POSIX_ERROR_BASE + 20)
#define ENOEXEC			(B_POSIX_ERROR_BASE + 21)
#define ENOLCK			(B_POSIX_ERROR_BASE + 22)
#define ENOMEM			(B_POSIX_ERROR_BASE + 23)
#define ENOSPC			(B_POSIX_ERROR_BASE + 24)
#define ENOSYS			(B_POSIX_ERROR_BASE + 25)
#define ENOTDIR			(B_POSIX_ERROR_BASE + 26)
#define ENOTEMPTY		(B_POSIX_ERROR_BASE + 27)
#define ENOTTY			(B_POSIX_ERROR_BASE + 28)
#define ENXIO			(B_POSIX_ERROR_BASE + 29)
#define EPERM			(B_POSIX_ERROR_BASE + 30)
#define EPIPE			(B_POSIX_ERROR_BASE + 31)
#define EROFS			(B_POSIX_ERROR_BASE + 32)
#define ESPIPE			(B_POSIX_ERROR_BASE + 33)
#define ESRCH			(B_POSIX_ERROR_BASE + 34)
#define EXDEV			(B_POSIX_ERROR_BASE + 35)
#define EFPOS			(B_POSIX_ERROR_BASE + 36)
#define ESIGPARM		(B_POSIX_ERROR_BASE + 37)
#define EDOM			(B_POSIX_ERROR_BASE + 38)
#define ERANGE			(B_POSIX_ERROR_BASE + 39)
#define EPROTOTYPE		(B_POSIX_ERROR_BASE + 40)
#define EPROTONOSUPPORT	(B_POSIX_ERROR_BASE + 41)
#define EPFNOSUPPORT	(B_POSIX_ERROR_BASE + 42)
#define EAFNOSUPPORT	(B_POSIX_ERROR_BASE + 43)
#define EADDRINUSE		(B_POSIX_ERROR_BASE + 44)
#define EADDRNOTAVAIL	(B_POSIX_ERROR_BASE + 45)
#define ENETDOWN		(B_POSIX_ERROR_BASE + 46)
#define ENETUNREACH		(B_POSIX_ERROR_BASE + 47)
#define ENETRESET		(B_POSIX_ERROR_BASE + 48)
#define ECONNABORTED	(B_POSIX_ERROR_BASE + 49)
#define ECONNRESET		(B_POSIX_ERROR_BASE + 50)
#define EISCONN			(B_POSIX_ERROR_BASE + 51)
#define ENOTCONN		(B_POSIX_ERROR_BASE + 52)
#define ESHUTDOWN		(B_POSIX_ERROR_BASE + 53)
/* #define _ERROR_54	(B_POSIX_ERROR_BASE + 54)	reserved */
#define ECONNREFUSED	(B_POSIX_ERROR_BASE + 55)
#define EHOSTUNREACH	(B_POSIX_ERROR_BASE + 56)
#define ENOPROTOOPT		(B_POSIX_ERROR_BASE + 57)
#define ENOBUFS			(B_POSIX_ERROR_BASE + 58)


#define EACCES			B_PERMISSION_DENIED
#define EINTR			B_INTERRUPTED
#define EIO				B_IO_ERROR
#define ETIMEDOUT		B_TIMED_OUT
#define EAGAIN 			B_WOULD_BLOCK	/* SysV compatibility */
#define EWOULDBLOCK 	B_WOULD_BLOCK	/* BSD compatibility */

/*
 * ---------------------------------------------------------------------------
			Mail Errors
 * ---------------------------------------------------------------------------
 */
enum
{
/* mail errors */
	B_MAIL_NO_DAEMON = B_MAIL_ERROR_BASE,
	B_MAIL_UNKNOWN_USER,
	B_MAIL_WRONG_PASSWORD,
	B_MAIL_UNKNOWN_HOST,
	B_MAIL_ACCESS_ERROR,
	B_MAIL_UNKNOWN_FIELD,
	B_MAIL_NO_RECIPIENT,
	B_MAIL_INVALID_MAIL
};
/*
 * ---------------------------------------------------------------------------
			Print Errors
 * ---------------------------------------------------------------------------
 */
enum
{
/* mail errors */
	B_NO_PRINT_SERVER = B_PRINT_ERROR_BASE
};

#endif
