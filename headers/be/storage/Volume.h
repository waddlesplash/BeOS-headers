//******************************************************************************
//
//	File:		Volume.h
//
//	Copyright 1995-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_VOLUME_H
#define	_VOLUME_H

#ifndef _OBJECT_H
#include <Object.h>
#endif

#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

//--------------------------------------------------------------------

class	BDatabase;
class	BStore;
class	BDirectory;
class	BFile;
class	BVolume;

long		mount_vol(const char *device);
long		unmount_vol(long volid);
long		format_device(const char *device, const char *volume_name);

long		count_volumes();
BVolume		volume_at(long index);
BVolume		volume_for_database(BDatabase *db);
BVolume		boot_volume();

class BVolume : public BObject {
	B_DECLARE_CLASS_INFO(BObject);

	friend class	BStore;
	friend class	BDirectory;
	friend class	BFile;

public:
						BVolume();
						BVolume(long volid);
virtual					~BVolume();

		long			Error();
		long			SetID(long volid);
		BDatabase *		Database();
		long			GetRootDirectory(BDirectory *dir);
		long			ID();
		double			Capacity();
		double			FreeBytes();
		long			GetName(char *name);
		long			GetDevice(char *device);
		bool			IsRemovable();
		bool			IsReadOnly();

private:
		long			get_info(struct vol_info *);

		long			fVolID;
		long			fErr;
};

#endif
