//******************************************************************************
//
//	File:		Table.h
//
//	Copyright 1994 Be Incorporated. All Rights Reserved.
//
//******************************************************************************/

#ifndef	_TABLE_H
#define	_TABLE_H

#ifndef _SUPPORT_KIT_H
#include <SupportKit.h>
#endif
#ifndef _STORAGE_DEFS_H
#include <StorageDefs.h>
#endif
#ifndef	_DATABASE_H
#include "Database.h"
#endif

/*-----------------------------------------------------------------*/
/*  Table flags
 */
#define	INDEX			0x0100

/*-----------------------------------------------------------------*/
class BTable : public BObject	{
	DECLARE_CLASS_INFO(BObject);
public:
		char		*Name();
		BDatabase	*Database();
		BTable		*Parent();
		BTable		*ChildAt(long i);	
		long		CountChildren();	
		long		CountRecords();		

		long		CountFields();
		bool		HasAncestor(BTable *a_table);
		bool		GetFieldInfo(long i,
						char *name,
						field_key *key,
						long *type,
						long *flags);

		bool		GetFieldInfo(char *name,
						field_key *key,
						long *type,
						long *flags);

		bool		GetFieldInfo(field_key a_prop,
						char *name,
						long *type,
						long *flags);
	
		field_key	AddRefField(char *field_name, long flags = 0);
		field_key	AddDataField(char *field_name, long flags = 0);
		field_key	AddStringField(char *field_name, long flags = 0);
		field_key	AddLongField(char *field_name, long flags = 0);
		field_key	AddTimeField(char *field_name, long flags = 0);
		long		ID();
		long		FieldType(field_key a_key);
		long		FieldType(char *fieldName);
		field_key	FieldKey(char *fieldName);
		field_key	FieldKey(char* fieldName, long field_type);

/*-----------------------------------------------------------------*/
private:

friend class BDatabase;
friend class BRecord;

		long		NameToIndex(char *name);
		void 		reload(  char *a_table_name,
						   long id,
						   long a_parent_id,
						   long *prop_list,
						   long prop_count,
						   BDatabase *owner);

		field_key	AddField(char *field_name, long field_type, long flags = 0);
					BTable(char *table_name,
					   			long id, 
					   			long parent_id,
					   			long *prop_list,
					   			long prop_count,
					   			BDatabase *owner);
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
};

#endif
