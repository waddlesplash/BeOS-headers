/******************************************************************************

	File:		SupportDefs.h

	Description:	Some common type definitions.

	Copyright 1993-96, Be Incorporated

******************************************************************************/

#ifndef _SUPPORT_DEFS_H
#define _SUPPORT_DEFS_H
#ifndef _ERRORS_H
#include <Errors.h>
#endif

#ifndef _SYS_TYPES_H
typedef unsigned long			ulong;
typedef unsigned int			uint;
typedef unsigned short			ushort;
#endif  /* _SYS_TYPES_H */

typedef unsigned char			uchar;
typedef unsigned char			bool;

typedef volatile long			vlong;
typedef volatile int			vint;
typedef volatile short			vshort;
typedef volatile char			vchar;

typedef volatile unsigned long	vulong;
typedef volatile unsigned int	vuint;
typedef volatile unsigned short	vushort;
typedef volatile unsigned char	vuchar;

#ifndef FALSE
#define FALSE		0
#endif
#ifndef TRUE
#define TRUE		1
#endif

#ifndef NULL
#define NULL 	(0)
#endif
#ifndef NIL
#define NIL		(0)
#endif

#ifdef __cplusplus
extern const char *B_EMPTY_STRING;		/* global variable for "" */
#endif

#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)>(b)?(a):(b))

/* Function pointer types */
typedef void	(*B_PFV)();
typedef int		(*B_PFI)();
typedef long	(*B_PFL)();

#ifdef __cplusplus
extern "C" {
#endif

/* ----------
   Time functions

	time is represented at the number of seconds since 00:00:00
	Jan 1 1970 Coordinated Universal Time (UTC).  The time zone is kept
	as an offset in seconds from the system time.  Library functions
	convert these to the local time.
----- */

ulong	real_time_clock (void);
void	set_real_time_clock (ulong secs_since_jan1_1970);

long	time_zone (void);
void	set_time_zone (long offset_from_utc);

/* ------
	Useful assembly language routines

	The atomic functions return the old value found in the value arg. 
----- */

extern long atomic_add(long *value, long addvalue);
extern long atomic_and(long *value, long andvalue);
extern long atomic_or(long *value, long orvalue);	

extern short	read_16_swap (short *address);
extern long		read_32_swap (long *address);
extern void		write_16_swap (short *address, short value);
extern void		write_32_swap (long *address, long value);

#ifdef __cplusplus
}
#endif



#endif
