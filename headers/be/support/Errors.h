/*

	Errors.h

    Copyright (c) 1994 by Be Incorporated.  All Rights Reserved.

*/

#ifndef _ERRORS_H
#define _ERRORS_H

#ifndef _LIMITS_H
#include <inc/limits.h>
#endif

/* general errors */
#define GENERAL_ERROR_BASE		LONG_MIN
#define OS_ERROR_BASE			GENERAL_ERROR_BASE + 0x1000
#define APP_ERROR_BASE			GENERAL_ERROR_BASE + 0x2000
#define INTERFACE_ERROR_BASE	GENERAL_ERROR_BASE + 0x3000
#define OTHER_ERROR_BASE		GENERAL_ERROR_BASE + 0x4000
#define MIDI_ERROR_BASE			GENERAL_ERROR_BASE + 0x5000
#define STORAGE_ERROR_BASE		GENERAL_ERROR_BASE + 0x6000

/* end of be-defined error constants; dev-defined errors start here(+1) */
#define BE_ERROR_END		(GENERAL_ERROR_BASE + 0xffff)

/*
 * ---------------------------------------------------------------------------
			General Errors
 * ---------------------------------------------------------------------------
 */
enum {
	NO_MEMORY = GENERAL_ERROR_BASE,	/* not enough memory to do something */
	IO_ERROR,					/* general io error */
	PERMISSION_DENIED,			/* probably just for files, but... */
	FILE_ERROR,					/* general file error */
	FILE_NOT_FOUND,				/* obvious */
	BAD_INDEX,					/* index not in range for the data set */
	BAD_TYPE,					/* bad argument type passed to function */
	BAD_VALUE,					/* bad argument value passed to function */
	NAME_NOT_FOUND,				/* given name not found */
	NAME_IN_USE,				/* for named token creation functions */

	SYS_ERROR = -1,				/* for the very laxy */
	NO_ERROR = 0
};

/*
 * ---------------------------------------------------------------------------
			OS Kit Errors
 * ---------------------------------------------------------------------------
 */
enum {
/* semaphore errors */
	BAD_SEM_ID = OS_ERROR_BASE,	/* operation request on an invalid semaphore */
	NO_MORE_SEMS,				/* all semaphore ids are taken */

/* thread errors */
	BAD_THREAD_ID = OS_ERROR_BASE + 0x100,	/* operation on an invalid thread */
	NO_MORE_THREADS,					/* all thread ids are taken */
	BAD_THREAD_STATE,					/* thread in inappropriate state. */
	BAD_TEAM_ID,						/* operation on an invalid team */
	NO_MORE_TEAMS,						/* all team ids are taken */

/* message port errors */
	BAD_PORT_ID = OS_ERROR_BASE + 0x200,/* operation request on an invalid port */
	NO_MORE_PORTS					/* all port ids are taken */
};


/*
 * ---------------------------------------------------------------------------
			App Kit Errors
 * ---------------------------------------------------------------------------
 */
enum
{
/* message/messenger errors */
	UNEXPECTED_REPLY = APP_ERROR_BASE,	/* replying to message that didn't want one */
	DUPLICATE_REPLY,				/* sending 1 replies to the same message */
	MESSAGE_TO_SELF					/* can't send message to self (same pid) */
};


/*
 * ---------------------------------------------------------------------------
			Other Errors
 * ---------------------------------------------------------------------------
 */

#endif
