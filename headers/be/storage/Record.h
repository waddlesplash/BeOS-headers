//******************************************************************************
//
//	File:		Record.h
//
//	Copyright 1994 Be Incorporated. All Rights Reserved.
//
//******************************************************************************/

#ifndef	_RECORD_H
#define	_RECORD_H

#ifndef _SUPPORT_KIT_H
#include <SupportKit.h>
#endif
#ifndef _STORAGE_DEFS_H
#include <StorageDefs.h>
#endif
#ifndef	_TABLE_H
#include "Table.h"
#endif
#ifndef _DATABASE_H
#include "Database.h"
#endif
#ifndef _TIME_H
#include <time.h>
#endif

/*-----------------------------------------------------------------*/

class	BRecord : public BObject {
	DECLARE_CLASS_INFO(BObject);
public:
					BRecord(BTable *);
					BRecord(BDatabase *, record_ref);
					BRecord(BRecord*);
virtual				~BRecord();

		long		Error();
		record_ref	Ref();
		BTable		*Table();
		BDatabase	*Database();

		record_ref	Commit();
		void		Remove();
		void		Update();
		void		Lock();
		void		Unlock();
		bool		IsNew();

		long		FindLong(char *field_name);
		long		FindLong(field_key);
		
		char		*FindString(char *field_name);
		char		*FindString(field_key);
		
		record_ref	FindRef(char *field_name);
		record_ref	FindRef(field_key);
		
		time_t		FindTime(char *field_name);
		time_t		FindTime(field_key);
		
		void		*FindRaw(char *field_name, long *size);
		void		*FindRaw(field_key, long *size);
		
		void		SetLong(char *field_name, long v);
		void		SetLong(field_key, long v);

		void		SetRef(char *field_name, record_ref);
		void		SetRef(field_key, record_ref);
		
		void		SetTime(char *field_name, time_t);
		void		SetTime(field_key, time_t);
		
		void		SetString(char *field_name, const char *a_string);
		void		SetString(field_key, const char *a_string);

		void		SetRaw(char *field_name, const void *data, long size);
		void		SetRaw(field_key, const void *data, long size);

/*-----------------------------------------------------------------*/
private:

friend class BDatabase;

		BTable		*the_table;
		char		*data_ptr;
		long		data_size;
		record_ref	ref;
		long		error;
		char		newone;
		bool		local_lock;

					BRecord(BTable *a_table, record_ref aref, char *data_ptr,
							long d_size);
		void		*get_ind_field_data(long i, long *fsize);
		void		set_data(long index, const char *new_data, long new_size);
		char 		*make_empty(long cnt, long *d_size);
		record_ref	commit_first();
		record_ref	commit_modify();
		bool		try_to_lock();
};

/*-----------------------------------------------------------------*/

#endif
