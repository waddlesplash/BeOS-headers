/******************************************************************************

	File:		SupportDefs.h

	Description:	Some common type definitions.

	Copyright 1993-96, Be Incorporated

******************************************************************************/

#ifndef _SUPPORT_DEFS_H
#define _SUPPORT_DEFS_H

typedef unsigned long			ulong;
typedef unsigned int			uint;
typedef unsigned short			ushort;
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

/* ??? remove */
typedef void	(*B_PFV)();
typedef int		(*B_PFI)();
typedef long	(*B_PFL)();

#ifndef _ERRORS_H
#include <Errors.h>
#endif

#endif
