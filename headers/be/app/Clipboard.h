//******************************************************************************
//
//	File:		Clipboard.h
//
//	Copyright 1994-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_CLIPBOARD_H
#define	_CLIPBOARD_H

#ifndef	_OBJECT_H
#include <Object.h>
#endif
#ifndef _OS_H
#include <OS.h>
#endif
#ifndef _MESSAGE_H
#include <Message.h>
#endif
#ifndef _LOCKER_H
#include <Locker.h>
#endif
#ifndef _STDDEF_H
#include <stddef.h>
#endif

extern "C" int	_init_clipboard_();

class BWindow;
class BApplication;

class BClipboard {

	// because BRoster is a shared object (across address spaces) it
	// can't have any virtual functions. Therefore it doesn't inherit from
	// BObject or participate in the Class Info system.

public:
		bool		Lock();
		void		Unlock();
		
		void		Clear();
		void		Commit();

		void		AddText(const char *string);
		void		AddData(ulong type, const void *data, long numBytes);

		const char	*FindText(long *numBytes);
		const void	*FindData(ulong type, long *numBytes, long index = 0);

		long		CountEntries(ulong type);

private:
friend BApplication;
friend BWindow;
friend int	_init_clipboard_();

		void		*operator new(size_t size, bool shared);
		void		operator delete(void *p, size_t size);
					BClipboard(	const char *name,
								bool fromDisk,
								BClipboard *sysClip = NULL);
					~BClipboard();

		void		UpdateFromSys();
		bool		CheckLock() const;

		long		fCount;
		BClipboard	*fSystemClip;
		long		fSystemCount;
		BMessage	fData;
		BLocker		fLock;
};

extern BClipboard *be_clipboard;

#endif
