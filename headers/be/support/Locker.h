//******************************************************************************
//
//	File:		Locker.h
//
//	Copyright 1992-97, Be Incorporated
//
//******************************************************************************

#pragma once

#ifndef	_LOCKER_H
#define	_LOCKER_H

#include <OS.h>
#include <SupportDefs.h>

//------------------------------------------------------------------------------

class BLocker {
public:
					BLocker();
					BLocker(const char *name);
virtual				~BLocker();	

		bool		Lock();
		void		Unlock();
		bool		IsLocked() const;

		// should only be used in special situations.
		status_t		LockWithTimeout(bigtime_t timeout);

		// following functions are useful for debugging.
		thread_id	LockingThread() const;
		int32		CountLocks() const;
		int32		CountLockRequests() const;
		sem_id		Sem() const;

private:
		bool		_Lock(bigtime_t timeout, status_t *error);

		int32		fCount;
		sem_id		fSem;
		int32		fOwner;
		int32		fOwnerCount;
};

#endif
