/* ++++++++++
	FILE:	joystick.h
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
