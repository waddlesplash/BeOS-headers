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

	B_ERROR = -1,				/* for the very lazy */
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


#endif
