/******************************************************************************

	File:		SupportDefs.h

	Description:	Some common type definitions.

	Copyright 1993-97, Be Incorporated

******************************************************************************/


#ifndef _SUPPORT_DEFS_H
#define _SUPPORT_DEFS_H

/*	??? should remove the 3 typedefs below and fix <sys/types.h> to always
	define them. */

#ifndef _SYS_TYPES_H
typedef unsigned long			ulong;
typedef unsigned int			uint;
typedef unsigned short			ushort;
#endif  /* _SYS_TYPES_H */

#include <sys/types.h>
#include <Errors.h>

typedef	signed char				int8;
typedef unsigned char			uint8;
typedef volatile signed char   	vint8;
typedef volatile unsigned char	vuint8;

typedef	short					int16;
typedef unsigned short			uint16;
typedef volatile short			vint16;
typedef volatile unsigned short	vuint16;

typedef	long					int32;
typedef unsigned long			uint32;
typedef volatile long			vint32;
typedef volatile unsigned long	vuint32;

typedef	long long					int64;
typedef unsigned long long			uint64;
typedef volatile long long			vint64;
typedef volatile unsigned long long	vuint64;

typedef int32					status_t;
typedef int64					bigtime_t;
typedef uint32					type_code;

/* change this to a 1 when we switch to the new compiler */
#if 1

#ifndef __cplusplus
/* for C code */
typedef unsigned char			bool;
#define false	0
#define true	1
#endif

#else

typedef unsigned char			bool;

#endif

/*	leave for compatibility with old code. Compiler will promote 0 and 1
	to false and true. */
#ifndef FALSE
#define FALSE		0
#endif
#ifndef TRUE
#define TRUE		1
#endif

typedef unsigned char			uchar;

typedef volatile long			vlong;
typedef volatile int			vint;
typedef volatile short			vshort;
typedef volatile char			vchar;

typedef volatile unsigned long	vulong;
typedef volatile unsigned int	vuint;
typedef volatile unsigned short	vushort;
typedef volatile unsigned char	vuchar;

typedef unsigned short          unichar;

#ifndef NULL
#define NULL 	(0)
#endif

#ifdef __cplusplus
extern const char *B_EMPTY_STRING;		/* global variable for "" */
#endif

/*
 * min and max are declared as templates in c++.
 */
#ifndef __cplusplus
#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)>(b)?(a):(b))
#endif /* __cplusplus */

#define min_c(a,b) ((a)>(b)?(b):(a))
#define max_c(a,b) ((a)>(b)?(a):(b))

/* Function pointer types */
typedef void	(*B_PFV)();
typedef int		(*B_PFI)();
typedef long	(*B_PFL)();

#ifdef __cplusplus
extern "C" {
#endif

/* ------
	Useful assembly language routines

	The atomic functions return the old value found in the value arg. 
----- */

extern int32 atomic_add(int32 *value, int32 addvalue);
extern int32 atomic_and(int32 *value, int32 andvalue);
extern int32 atomic_or(int32 *value, int32 orvalue);	

extern int16	read_16_swap (const int16 *address);
extern int32	read_32_swap (const int32 *address);
extern void		write_16_swap (int16 *address, int16 value);
extern void		write_32_swap (int32 *address, int32 value);

#ifdef __cplusplus
}
#endif



#endif
