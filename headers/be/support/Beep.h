/******************************************************************************

	File:			Beep.h

	Description:	Interface for a simple beep sound.

	Copyright 1995-97, Be Incorporated

******************************************************************************/


#ifndef _BEEP_H
#define _BEEP_H

#include <SupportDefs.h>

/* Personalized beep file (this isn't implemented yet) */
#define B_SYSTEM_BEEP_FILE		"beep.snd"

status_t beep();

#endif			// #ifndef _BEEP_H
