//******************************************************************************
//
//	File:		Table.h
//
//	Copyright 1994-96 Be Incorporated. All Rights Reserved.
//
//******************************************************************************/

#ifndef	_TABLE_H
#define	_TABLE_H

#ifndef _STORAGE_DEFS_H
#include <StorageDefs.h>
#endif
#ifndef	_DATABASE_H
#include "Database.h"
#endif

/*-----------------------------------------------------------------*/
/*  Table flags
 */
#define	B_INDEXED_FIELD			0x0100

class BDatabase;

/*-----------------------------------------------------------------*/
class BTable : public BObject	{
	B_DECLARE_CLASS_INFO(BObject);
public:
		char		*Name();
		BDatabase	*Database();
		BTable		*Parent();
		BTable		*ChildAt(long i);	
		long		CountChildren();	
		long		CountFields();
		bool		HasAncestor(BTable *a_table);
		bool		HasAncestor(const char *table_name);
		void		SetTypeAndApp(ulong type, ulong creator);
		void		GetTypeAndApp(ulong *type, ulong *creator);
		bool		GetFieldInfo(long i,
								 char *name,
								 field_key *key,
								 long *type,
								 long *flags);

		bool		GetFieldInfo(const char *name,
								 field_key *key,
						 		 long *type,
								 long *flags);

		bool		GetFieldInfo(field_key a_prop,
								 char *name,
								 long *type,
								 long *flags);
	
		field_key	AddRecordIDField(const char *field_name, long flags = 0);
		field_key	AddRawField(const char *field_name, long flags = 0);
		field_key	AddStringField(const char *field_name, long flags = 0);
		field_key	AddLongField(const char *field_name, long flags = 0);
		field_key	AddTimeField(const char *field_name, long flags = 0);
		long		ID();
		long		FieldType(field_key a_key);
		long		FieldType(const char *fieldName);
		field_key	FieldKey(const char *fieldName);
		field_key	FieldKey(const char* fieldName, long field_type);

/*-----------------------------------------------------------------*/
private:

friend class BDatabase;
friend class BRecord;

		long		NameToIndex(const char *name);
		void 		reload(  char *a_table_name,
						   long id,
						   long a_parent_id,
						   long *prop_list,
						   long prop_count,
						   BDatabase *owner,
						   ulong type,
						   ulong creator);

		field_key	AddField(const char *field_name, long field_type, long flags = 0);
					BTable(char *table_name,
					   			long id, 
					   			long parent_id,
					   			long *prop_list,
					   			long prop_count,
					   			BDatabase *owner,
								ulong type,
								ulong creator);
					~BTable();
		long		GetParentId();
		void		refresh_info();
		long		PropToIndex(long prop);

		char		*table_name;
		BDatabase	*parent_database;
		long		table_id;
		long		parent_id;
		long		*fprop_list;
		long		fprop_count;
		ulong		table_type;
		ulong		table_creator;
};

#endif
