/* ++++++++++

	BeDefs.h

	Copyright (C) 1991-93 Be, Inc.  All Rights Reserved.
	Some common type definitions.

+++++ */

#ifndef _BE_DEFS_H
#define _BE_DEFS_H

typedef unsigned long	ulong;
typedef unsigned int	uint;
typedef unsigned short	ushort;
typedef unsigned char	uchar;
typedef unsigned char	bool;

#ifndef FALSE
#define FALSE		0
#endif
#ifndef TRUE
#define TRUE		1
#endif

#ifndef NULL
#define NULL 		((void *)0)
#endif
#ifndef NIL
#define NIL		0L
#endif

#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)>(b)?(a):(b))
#define trace() printf("%s %d pid=%d\n", __FILE__, __LINE__, getpid());

typedef void	(*PFV)();
typedef int	(*PFI)();
typedef long	(*PFL)();

#ifndef MAX_WORD
#define MAX_WORD ((short)(0x7FFF))
#endif
#ifndef MIN_WORD
#define MIN_WORD ((short)(0x8000))
#endif
#ifndef MAX_UWORD
#define MAX_UWORD ((short)(0xFFFF))
#endif

#ifndef MIN_INT
#define MIN_INT (0x80000000L)
#endif
#ifndef MAX_INT
#define MAX_INT (0x7fffffffL)
#endif

#ifndef MIN_LONG
#define MIN_LONG MIN_INT
#endif
#ifndef MAX_LONG
#define MAX_LONG MAX_INT
#endif
#ifndef MAX_ULONG
#define MAX_ULONG (0xFFFFFFFFL)
#endif

/* Event contexts */

enum {
	SYS_EVENT,
	COMMAND_EVENT
};

/* Event codes */
enum {
	WINDOW_RESIZED = MIN_INT,
	WINDOW_MOVED,
	CLOSE_REQUESTED,
	ACTIVATION,
	MOUSE_DOWN,
	MOUSE_UP,
	MOUSE_MOVED,
	PARCEL_DROPPED,
	TICK,
	KEY_DOWN,
	VALUE_CHANGED,
	VIEW_RESIZED,
	VIEW_MOVED,
	KEY_UP,
	PUBLIC_EVENT_END = (WINDOW_RESIZED + 0xffff)
};

/* window part codes */

enum {
	UNKNOWN_AREA,
	TITLE_BAR,
	CONTENT_AREA,
	RESIZE_AREA,
	CLOSE_BOX
};

/* general errors */

enum {
	NO_MEMORY = MIN_INT,	/* not enough memory to do something */
	IO_ERROR,		/* general io error */
	PERMISSION_DENIED,	/* probably just for files, but... */

	FILE_ERROR,		/* general file error */
	FILE_NOT_FOUND,		/* obvious */

	BAD_ARG_TYPE,		/* bad argument type passed to function */
	BAD_ARG_VALUE,		/* bad argument value passed to function */

	NAME_NOT_FOUND,		/* for named token look-up failure */
	NAME_IN_USE,		/* for named token creation functions */

/* semaphore errors */
	BAD_SEM_ID,		/* operation requested on an invalid semaphore */
	NO_MORE_SEMS,		/* all semaphore ids are currently taken. */

/* task errors */
	BAD_TASK_ID,		/* operation requested on an invalid task */

/* archive errors */
	BAD_RESOURCE_ID,	/* operation requested on an invalid resource */
	NO_ARCHIVE,		/* named archive file not found */
	DUPLICATE_RESOURCE,	/* currently unused */

/* modem errors */
	MODEM_ERROR,
	MODEM_BUSY,
	MODEM_NO_CARRIER,

/* BDataPort errors */
	DATA_PORT_ERROR,

/* end of be-defined error constants; dev-defined errors start here(+1) */
	BE_ERROR_END = (NO_MEMORY + 0xffff),

	SYS_ERROR = -1,		/* for the very lazy */
	NO_ERROR = 0
};

/* Data types */
enum {
	CHAR_TYPE,
	SHORT_TYPE,
	LONG_TYPE,
	UCHAR_TYPE,
	USHORT_TYPE,
	ULONG_TYPE,	
	FLOAT_TYPE,
	DOUBLE_TYPE,
	POINT_TYPE,
	RECT_TYPE,
	RGB_COLOR_TYPE,
	PATTERN_TYPE,
	ASCII_TYPE,
	RTF_TYPE,
	MONOCHROME_1_BIT_TYPE,
	GRAYSCALE_8_BIT_TYPE,
	COLOR_8_BIT_TYPE,
	RGB_24_BIT_TYPE,
	TIFF_TYPE,
	FILE_TYPE,
	PARCEL_TYPE,
	ALL_TYPES
};

#endif
