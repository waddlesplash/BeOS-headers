//******************************************************************************
//
//	File:		Database.h
//
//	Copyright 1994-96 Be Incorporated. All Rights Reserved.
//
//******************************************************************************/

#ifndef	_DATABASE_H
#define	_DATABASE_H

#ifndef _MESSENGER_H
#include <Messenger.h>
#endif
#ifndef	_QUERY_H
#include "Query.h"
#endif

/*------------------------------------------------------------*/

#define	B_MAX_TABLE_COUNT		256
#define	B_INDEX_NEEDED	-2
#define	B_NO_DATABASE			-3

/*------------------------------------------------------------*/

class BTable;
class BRecord;
class BDF;

class	BDatabase : public BObject {
	B_DECLARE_CLASS_INFO(BObject);
public:
		long		Error();
		database_id	xID();
		long		VolumeID();

		BTable		*CreateTable(const char *table_name);
		BTable		*CreateTable(const char *table_name, const char *parent_name);
		BTable		*CreateTable(const char *table_name, BTable *parent_table);
		BTable		*FindTable(const char *table_name);
		long		Sync();
		long		CountTables();
		BTable		*TableAt(long i);
		bool		IsValid();
		bool		IsReadOnly();
		long		ID();
		long		Version();

		void		PrintToStream();
		long		GetTag(long index);
		void		SetTag(long index, long value);

/*------------------------------------------------------------*/
private:
friend class BQuery;
friend class BTable;
friend class BRecord;
friend int	_add_volume_(long, long, long *);	// ## from Volume.cpp
friend int	_remove_volume_(long);				// ## from Volume.cpp
friend class BVolCtrl;							// ## from zoo_keeper

					BDatabase(const char *name, long volID);
					BDatabase(long server_id);
virtual				~BDatabase();
		long		Create(long volID);
		long		MakeIndex();

		long		DoGet(long ref,
						  BTable **the_table,
						  char 	 **the_data,
						  long 	 *a_size);
		long		private_close(bool delete_datafile);
		void		get_load_vector(char *load_vector);
		int			load_table_list();
		BTable 		*load_table(long id);
		void		display_tree1(long index, long parent_id, long level);
		BMessage	*DoQuery(BQuery *a_query);
		BMessage	*DoQuery(BQuery *a_query, long ref);
		void		preload();
		long		*reload_table_info(long id, long *pl_size);
		BTable 		*reload_table(long id, BTable *a_table);
		long		do_reserve();
		void		remove_reserve(long ref);

		BMessenger	messenger;
		long		signature;
		long		db_id;
		database_id	db_sid;
		long		error;
		long		vol_id;
		char		*database_name;
		BTable		*table_list[B_MAX_TABLE_COUNT];
		BDF			*datafile;
		bool		read_only;
		long		unique;
		long		version;
};
	
BDatabase	*database_for(database_id id);
long		master_hash(const char *name, long type);

#endif
