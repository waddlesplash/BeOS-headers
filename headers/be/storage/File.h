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

struct	rf_header;
struct	hole_ent;
struct	hash_ent;
struct	res_ent;
struct	type_ent;

extern "C" int	close(int);


class BFile : public BStore {
	B_DECLARE_CLASS_INFO(BStore);

	friend class	BStore;
	friend class	BDirectory;
	friend class	BPosixServer;

public:
						BFile();
						BFile(record_ref ref);
virtual					~BFile();

		long			CopyTo(BDirectory *dir, const char *name, BFile *file,
							store_creation_hook *f = NULL, void *d = NULL);

		long			Size();
		long			DataSize();
		long			ResourcesSize();

		long			GetTypeAndApp(ulong *type, ulong *creator);
		long			SetTypeAndApp(ulong type, ulong creator);

		long			OpenResources(bool towrite = FALSE);
		long			OpenData();
		long			CloseResources();
		long			CloseData();

		long			Seek(long pos, long mode);
		long			Read(void *buf, long numBytes);
		long			Write(const void *buf, long numBytes);
		long			SetDataSize(long eof);

		long			AddResource(const char *name,
									ulong type,
									const void *data,
									long numBytes);
		long			RemoveResource(	const char *name,
										ulong type,
										long index = 0);
		void			*FindResource(	const char *name,
										ulong type,
										long *numBytes);
		void			*FindResource(	const char *name,
										ulong type,
										long index,
										long *numBytes);
		long			ReplaceResource(const char *name,
										ulong type,
										void *data,
										long numBytes);
		long			ReplaceResource(const char *name,
										ulong type,
										long index,
										void *data,
										long numBytes);
		bool			HasResource(const char *name,
									ulong type,
									long index = 0);

		long			CountResources(const char *name, ulong type);
		bool			GetResourceInfo(long resIndex,
										char* nameFound,
										ulong* typeFound,
										long* countFound = NULL);
		bool			GetResourceInfo(ulong type, long resIndex,
										char* nameFound,
										long* countFound = NULL);
		bool			GetResourceInfo(char* name, long resIndex,
										ulong* typeFound,
										long* countFound = NULL);

private:
virtual	bool			is_file();

virtual	long			set_ref(long volid, record_id id);

		void			set_type_creator(ulong type, ulong creator);
		void			set_icon();
		bool			test_and_extract_icons(ulong *type, ulong *creator);

		int				copy_file(int sfd, int dfd);
		int				register_open(bool resfork);
		int				register_close(bool resfork);

		bool			get_resource_info(	ulong type, long resIndex,
											char* nameFound,
											ulong* typeFound,
											long* countFound);

		int				create_fork();
		int				new_map();
		int				read_map();
		int				write_map();
		int				close_map();
		long			resource_file_size();
		int				compress_resources(int nfd);
		int				compress_resource_file();
	
		ulong			hash(const char *name);

		long			new_hole(long offset, long size);
		long			find_hole(long size);
		long			change_block(long offset, long oldsize, long newsize);
		long			shrink_block(long offset, long oldsize, long newsize);
		long			grow_block(long offset, long oldsize, long newsize);
		long			grow_hash_dir();
		long			grow_hash_tab();
		long			grow_res_tab();
		
		long			find_type(ulong type);
		long			add_type(ulong type);
		void			remove_type(long tp);

		long			find_res_ent(const char *name, ulong type, long index);
		long			add_res_ent(const char *name, ulong type);
		void			remove_res_ent(long ent);

		int				fDfd;
		bool			fRopen;
		int				fRfd;
		bool			fToWrite;

		rf_header		*rfh;
		hash_ent		*hash_tab;
		long			*hash_dir;
		type_ent		*type_dir;
		hole_ent		*hole_tab;
		res_ent			*res_tab;
		bool			other_tabs_dirty;
		bool			hole_tab_dirty;
};

#endif
