/******************************************************************************

	File:		SupportDefs.h

	Description:	Some common type definitions.

	Copyright 1993-94, Be Incorporated

******************************************************************************/

#ifndef _SUPPORT_DEFS_H
#define _SUPPORT_DEFS_H

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
#define NULL 	(0)
#endif
#ifndef NIL
#define NIL		(0)
#endif

#ifdef __CPLUSPLUS__
extern const char *EMPTY_STRING;		/* global variable for "" */
#endif

#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)>(b)?(a):(b))
#define trace() printf("%s %d pid=%d\n", __FILE__, __LINE__, getpid()); /* ??? remove */

/* ??? remove */
typedef void	(*PFV)();
typedef int		(*PFI)();
typedef long	(*PFL)();

#ifndef _ERRORS_H
#include <support/Errors.h>
#endif

#endif
