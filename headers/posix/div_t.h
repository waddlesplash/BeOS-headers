/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	div_t.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __div_t__
#define __div_t__


typedef struct {
	int	quot;
	int	rem;
} div_t;

typedef struct {
	long	quot;
	long	rem;
} ldiv_t;

#pragma options align=reset

#endif
/*     Change record
*/
