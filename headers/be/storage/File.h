//******************************************************************************
//
//	File:		File.h
//
//	Copyright 1995-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_FILE_H
#define	_FILE_H

#ifndef _OS_H
#include <OS.h>
#endif

#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

#ifndef	_STORE_H
#include <Store.h>
#endif

#ifndef	_DIRECTORY_H
#include <Directory.h>
#endif

//--------------------------------------------------------------------

class BFile : public BStore {
	B_DECLARE_CLASS_INFO(BStore);

	friend class	BStore;
	friend class	BDirectory;
	friend class	BPosixServer;

public:
						BFile();
						BFile(record_ref ref);
virtual					~BFile();

virtual	long			FileCreated();

		long			CopyTo(BDirectory *dir, const char *name, BFile *file,
							store_creation_hook *f = NULL, void *d = NULL);
		long			SwitchWith(BFile *file);
		
		long			Size();
		long			SetSize(long numBytes);

		long			GetTypeAndApp(ulong *type, ulong *creator);
		long			SetTypeAndApp(ulong type, ulong creator);

virtual	long			Open(long open_mode);
		bool			IsOpen(void);
		long			OpenMode(void);
virtual	long			Close(void);

		long			Seek(long pos, long seek_mode);
		long			Read(void *buf, long numBytes);
		long			Write(const void *buf, long numBytes);

private:
virtual	bool			is_file();

virtual	long			set_ref(long volid, record_id id);

		void			set_type_creator(ulong type, ulong creator);
		void			set_icon();
		bool			test_and_extract_icons(ulong *type, ulong *creator);

		int				copy_file(int sfd, int dfd);

		int				fFd;
		bool			fReadOnly;
};

#endif
