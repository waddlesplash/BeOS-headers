/*****************************************************************************
//
//	File:		Volume.h
//
//	Description:	BVolumeRoster class.  Iterate over mounted volumes,
//					and watch volumes as they're mounted and unmounted.
//
//	Copyright 1992-97, Be Incorporated
//
//****************************************************************************/
#pragma once

#ifndef _VOLUME_ROSTER_H
#define _VOLUME_ROSTER_H

#include <OS.h>
#include <Volume.h>
#include <Application.h>
class BVolume;
class BMessenger;

class BVolumeRoster {

public:
						BVolumeRoster();
virtual					~BVolumeRoster();

		status_t		GetNextVolume(BVolume *vol);
		void			Rewind();

		status_t		GetBootVolume(BVolume *vol);
		status_t		StartWatching(BMessenger msngr=be_app_messenger);

		void			StopWatching(void);

		BMessenger		Messenger(void) const;

private:

virtual	void		_SeveredVRoster1();
virtual	void		_SeveredVRoster2();

		int32			fPos;
		BMessenger		*fTarget;


};

#endif
