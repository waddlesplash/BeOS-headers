
/*****************************************************************************
//
//	File:		Volume.h
//
//	Description:	BVolume class
//
//	Copyright 1992-97, Be Incorporated
//
//****************************************************************************/
#pragma once

#ifndef _VOLUME_H
#define _VOLUME_H

#include <sys/types.h>
#include <SupportDefs.h>

class	BDirectory;

class BVolume {
public:
							BVolume();
							BVolume(dev_t dev);
							BVolume(const BVolume &vol);

virtual						~BVolume();

			status_t		InitCheck() const;

			status_t		SetTo(dev_t dev);
			void			Unset(void);

			dev_t			Device() const;

			status_t		GetRootDirectory(BDirectory *dir) const;

			off_t			Capacity() const;
			off_t			FreeBytes() const;

			status_t		GetName(char *name) const;
			status_t		SetName(const char *name);
		
			bool			IsRemovable() const;
			bool			IsReadOnly() const;
			bool			IsPersistent() const;
			bool			IsShared() const;
			bool			KnowsMime() const;
			bool			KnowsAttr() const;
			bool			KnowsQuery() const;
		
			bool			operator==(const BVolume &vol) const;
			bool			operator!=(const BVolume &vol) const;
			BVolume &		operator=(const BVolume &vol);

private:

friend class BVolumeRoster;

virtual	void		_TurnUpTheVolume1();
virtual	void		_TurnUpTheVolume2();

		dev_t			fDev;
		status_t		fCStatus;
};



#endif
