//******************************************************************************
//
//	File:		Autolock.h
//
//	Description:	stack based auto locking/unlocking class
//
//	Copyright 1996-97, Be Incorporated
//
//******************************************************************************

#pragma once

#ifndef	_AUTOLOCK_H
#define	_AUTOLOCK_H

#include <Locker.h>
#include <Looper.h>

class BAutolock {

public:
					BAutolock(BLocker *lock);
					BAutolock(BLocker &lock);
					BAutolock(BLooper *looper);
					~BAutolock();
		
		bool		IsLocked();

private:
		BLocker		*fLock;
		BLooper	*fLooper;
		bool		fLocked;
};

inline BAutolock::BAutolock(BLooper *looper)
{
	fLooper = looper;
	fLock = NULL;
	fLocked = fLooper->Lock();
}

inline BAutolock::BAutolock(BLocker *lock)
{
	fLooper = NULL;
	fLock = lock;
	fLocked = fLock->Lock();
}

inline BAutolock::BAutolock(BLocker &lock)
{
	fLooper = NULL;
	fLock = &lock;
	fLocked = fLock->Lock();
}

inline BAutolock::~BAutolock()
{
	if (fLocked) {
		if (fLock)
			fLock->Unlock();
		else
			fLooper->Unlock();
	}
}

inline bool BAutolock::IsLocked()
{
	return fLocked;
}

#endif
