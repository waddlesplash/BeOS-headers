//******************************************************************************
//
//	File:		Directory.h
//
//	Copyright 1995-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_DIRECTORY_H
#define	_DIRECTORY_H

#ifndef _OS_H
#include <OS.h>
#endif

#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

#ifndef	_STORE_H
#include <Store.h>
#endif

#ifndef	_FILE_H
#include <File.h>
#endif

//--------------------------------------------------------------------

class BDirectory : public BStore {
	B_DECLARE_CLASS_INFO(BStore);

	friend class	BStore;
	friend class	BFile;

public:
						BDirectory();
						BDirectory(record_ref ref);
virtual					~BDirectory();

		long			Create(const char *name, BStore *item,
							const char *table_name = NULL,
							store_creation_hook *f = NULL, void *d = NULL);
		long			Remove(BStore *item);

		bool			Contains(const char *name);
		bool			IsDirectory(const char *name);

		long			CountStores();
		long			CountFiles();
		long			CountDirectories();

		long			GetFile(const char *name, BFile *file);
		long			GetFile(long index, BFile *file);
		long			GetDirectory(const char *name, BDirectory *dir);
		long			GetDirectory(long index, BDirectory *dir);
	
		long			GetStores(long index, long num, record_ref *buf);
		long			GetFiles(long index, long num, record_ref *buf);
		long			GetDirectories(long index, long num, record_ref *buf);

private:
virtual	bool			is_file();
		int				create(const char *name, BStore *item,
							const char *table_name,	BRecord *model,
							store_creation_hook *f, void *d);
		int				find_indexed_item(long index, BStore *item);
		int				find_named_item(const char *name, BStore *item);
		long			count_items(bool files, bool dirs);
		int				find_items(bool files, bool dirs, long index,
							long num, record_ref *buf);
};

#endif
