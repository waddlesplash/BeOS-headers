//******************************************************************************
//
//	File:		Locker.h
//
//	Copyright 1992-96, Be Incorporated
//
//******************************************************************************

#ifndef	_LOCKER_H
#define	_LOCKER_H

#ifndef _OS_H
#include <OS.h>
#endif
#ifndef _OBJECT_H
#include <Object.h>
#endif
#ifndef _STDDEF_H
#include <stddef.h>
#endif

//------------------------------------------------------------------------------
extern "C" int	_init_shared_heap_();

class BLocker : public BObject {
	B_DECLARE_CLASS_INFO(BObject);
public:
		void		*operator new(size_t size);

					BLocker();
					BLocker(const char *name);
virtual				~BLocker();	

		bool		Lock();
		void		Unlock();
		thread_id	LockOwner() const;
		bool		CheckLock() const;

private:
friend int	_init_shared_heap_();
		
		void	*operator new(size_t size, void *buffer);

		long	fCount;
		sem_id	fSem;
		long	fOwner;
		int		fOwnerCount;
};

inline thread_id BLocker::LockOwner() const
	{ return fOwner; }

inline bool BLocker::CheckLock() const
	{ return (fOwner == find_thread(NULL)); }

#endif
