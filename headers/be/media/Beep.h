/******************************************************************************

	File:			Beep.h

	Description:	Interface for a simple beep sound.

	Copyright 1995-96, Be Incorporated

******************************************************************************/

#ifndef _BEEP_H
#define _BEEP_H

#ifndef _OS_H
#include <OS.h>
#endif

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifndef _STORAGE_DEFS_H
#include <StorageDefs.h>
#endif

typedef sem_id sound_handle;

/* Personalized beep file (this isn't implemented yet) */
#define B_SYSTEM_BEEP_FILE		"beep.snd"

sound_handle beep();

sound_handle play_sound(record_ref soundRef,
						bool mix,
						bool queue,
						bool background
						);

long stop_sound(sound_handle handle);

long wait_for_sound(sound_handle handle);

#endif			// #ifndef _BEEP_H
