/*
 *	stddef.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __stddef__
#define __stddef__

typedef long	ptrdiff_t;

#include <size_t.h>
#include <wchar_t.h>
#include <null.h>

#define offsetof(type, member)	((size_t) &(((type *) 0)->member))

#endif /* __stddef__ */
