//******************************************************************************
//
//	File:		Record.h
//
//	Copyright 1994-96 Be Incorporated. All Rights Reserved.
//
//******************************************************************************/

#ifndef	_RECORD_H
#define	_RECORD_H

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

bool does_ref_conform(record_ref ref, char* table_name);

/*-----------------------------------------------------------------*/


/*-----------------------------------------------------------------*/

class	BRecord : public BObject {
	B_DECLARE_CLASS_INFO(BObject);
public:
					BRecord(BDatabase* db, record_id id);
					BRecord(record_ref ref);
					BRecord(BTable *table);
					BRecord(BRecord *record);
virtual				~BRecord();

		long		Error();
		record_ref	Ref();
		record_id	ID();
		BDatabase	*Database();
		BTable		*Table();

		record_id	Commit();
		void		Delay();
		void		ReleaseDelay();		//might be private ??
		void		Remove();
		void		Update();
		void		Lock();
		void		Unlock();
		bool		IsNew();

		long		FindLong(const char *field_name);
		long		FindLong(field_key);
		
		double		FindDouble(const char *field_name);
		double		FindDouble(field_key);
		
		const char	*FindString(const char *field_name);
		const char	*FindString(field_key);
		
		record_id	FindRecordID(const char *field_name);
		record_id	FindRecordID(field_key);
		
		double	FindTime(const char *field_name);
		double	FindTime(field_key);
		
		void		*FindRaw(const char *field_name, long *size);
		void		*FindRaw(field_key, long *size);
		
		void		SetLong(const char *field_name, long v);
		void		SetLong(field_key, long v);

		void		SetDouble(const char *field_name, double v);
		void		SetDouble(field_key, double v);
		
		void		SetRecordID(const char *field_name, record_id id);
		void		SetRecordID(field_key key, record_id id);
		
		void		SetTime(const char *field_name, double);
		void		SetTime(field_key, double);
		
		void		SetString(const char *field_name, const char *a_string);
		void		SetString(field_key, const char *a_string);

		void		SetRaw(const char *field_name, const void *data, long size);
		void		SetRaw(field_key, const void *data, long size);

/*-----------------------------------------------------------------*/
private:

friend class BDatabase;

		int			lock;
		BTable		*the_table;
		char		*data_ptr;
		long		data_size;
		record_id	id;
		long		error;
		char		newone;
		char		has_been_delayed;
		bool		local_lock;
		bool		dirty;

					BRecord(BTable *a_table, record_id an_id, char *data_ptr,
							long d_size);
		void		*get_ind_field_data(long i, long *fsize);
		void		set_data(long index, const char *new_data, long new_size);
		char 		*make_empty(long cnt, long *d_size);
		record_id	commit_first(bool delay_notify);
		record_id	commit_modify(bool delay_notify);
		bool		try_to_lock();
		void		Reset(BDatabase *a_db, record_id an_id);
		void		Reset(BTable *a_table);
					BRecord();
		void		private_unlock();
		void		private_lock();
};

/*-----------------------------------------------------------------*/

#endif
