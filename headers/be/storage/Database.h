//******************************************************************************
//
//	File:		Database.h
//
//	Copyright 1994 Be Incorporated. All Rights Reserved.
//
//******************************************************************************/

#ifndef	_DATABASE_H
#define	_DATABASE_H

#ifndef _APP_KIT_H
#include <AppKit.h>
#endif
#ifndef	_QUERY_H
#include "Query.h"
#endif

/*------------------------------------------------------------*/

#define	MAX_TABLE		256
#define	DB_NEEDINDEX	-2
#define	DB_NODB			-3

/*------------------------------------------------------------*/

class BTable;
class BRecord;
class BDF;

class	BDatabase : public BMessenger {
	DECLARE_CLASS_INFO(BMessenger);
public:
					BDatabase(char *name, long volID);
virtual				~BDatabase();

		long		Error();
		long		Create(char *name, long volID);
		long		MakeIndex();

		BTable		*CreateTable(char *table_name);
		BTable		*CreateTable(char *table_name, char *parent_name);
		BTable		*CreateTable(char *table_name, BTable *parent_table);
		BTable		*FindTable(char *table_name);
		long		Sync();
		long		CountTables();
		BTable		*TableAt(long i);
		bool		IsValid();

		void		PrintToStream();

/*------------------------------------------------------------*/
private:
friend class BQuery;
friend class BTable;
friend class BRecord;

		long		GetSId();
		long		GetId();
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

		long		db_id;
		long		db_sid;
		long		error;
		char		*database_name;
		BTable		*table_list[MAX_TABLE];
		BDF			*datafile;
};
	
BDatabase	*id_to_database(long id);
long		master_hash(char *name, long type);

#endif
