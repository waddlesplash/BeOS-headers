/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	div_t.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __div_t__
#define __div_t__

#include <ansi_parms.h>                 /* mm 970905*/

/* #pragma options align=native */
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

typedef struct {
	int	quot;
	int	rem;
} div_t;

typedef struct {
	long	quot;
	long	rem;
} ldiv_t;

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
/* #pragma options align=reset */

#endif

/*     Change record
 * mm 970905  added include of ansi_parms.h to avoid need for prefix file
 */
