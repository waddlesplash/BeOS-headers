/* ++++++++++
	FILE:	joystick.h
	REVS:	$Revision: 1.1 $
	NAME:	herold
	DATE:	Tue Nov 14 11:48:18 PST 1995
	Copyright (c) 1995-96 by Be Incorporated.  All Rights Reserved.
+++++ */

#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

typedef struct joystick {
	double	timestamp;
	uint	horizontal;
	uint	vertical;
	bool	button1;
	bool	button2;
} joystick;

#endif
