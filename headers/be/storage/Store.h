//******************************************************************************
//
//	File:		Store.h
//
//	Copyright 1995-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_STORE_H
#define	_STORE_H

#ifndef _OBJECT_H
#include <Object.h>
#endif

#ifndef _RECORD_H
#include <Record.h>
#endif

#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

#ifndef _STORAGE_DEFS_H
#include <StorageDefs.h>
#endif

//--------------------------------------------------------------------

extern "C" int	_bfile_cleanup_();
class			BLocker;
class			BStore;
class			BVolume;
class			BDirectory;



typedef		long	store_creation_hook(BStore *, void *);

extern "C" long		get_ref_for_path(const char *, record_ref *);

class BStore : public BObject {
	B_DECLARE_CLASS_INFO(BObject);

public:
virtual					~BStore();

		long			Error();

		long			SetRef(record_ref ref);
		long			SetRef(BVolume *vol, record_id id);
		long			SetRef(long volid, record_id id);

		long			MoveTo(BDirectory *dir, const char *newname = NULL,
							store_creation_hook *f = NULL, void *d = NULL);

		long			GetParent(BDirectory *dir);

		long			GetPath(char *buffer, long bufsize);

		long			VolumeID();
		BRecord	*		Record();
		long			GetName(char *buffer);
		long			SetName(const char *name);
		long			CreationTime();
		long			ModificationTime();
		long			SetModificationTime(const long date);

		bool			operator==(const BStore &item);
		bool			operator!=(const BStore &item);
		BStore &		operator=(const BStore &item);

protected:
		long			SetError(long err);

private:
	friend int		_bfile_cleanup_();
	friend int		_add_volume_(long, long, long *);
	friend int		_remove_volume_(long);

						BStore();

	friend class	BDirectory;
	friend class 	BFile;

virtual	bool			is_file() = 0;
virtual long			set_ref(long volid, record_id id);

		record_id		fRecid;
		BRecord			*fRec;
		long			fVolID;
   		long			fErr;
};

#endif
