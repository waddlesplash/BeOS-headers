//******************************************************************************
//
//	File:		Clipboard.h
//
//	Copyright 1994-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************


#ifndef	_CLIPBOARD_H
#define	_CLIPBOARD_H

#include <OS.h>
#include <Messenger.h>
#include <Message.h>
#include <Locker.h>
#include <stddef.h>

class BWindow;
class BApplication;

class BClipboard {
public:
					BClipboard(const char *name, bool transient = FALSE);
virtual				~BClipboard();

		const char	*Name() const;

		bool		Lock();
		void		Unlock();
		
		status_t	Clear();
		status_t	Commit();

		BMessenger	DataSource() const;
		BMessage	*Data() const;

private:

					BClipboard(const BClipboard &);
		BClipboard	&operator=(const BClipboard &);

virtual	void		_ReservedClipboard1();
virtual	void		_ReservedClipboard2();
virtual	void		_ReservedClipboard3();

		bool		AssertLocked() const;
		status_t	DownloadFromSystem();
		status_t	UploadToSystem();
		bool		IsLocked() const;

		uint32		fCount;
		BMessage	*fData;
		BLocker		fLock;
		BMessenger	fClipHandler;
		BMessenger	fDataSource;
		uint32		fSystemCount;
		char		*fName;
		uint32		_reserved[4];
};

extern BClipboard *be_clipboard;

#endif
