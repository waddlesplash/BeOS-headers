//******************************************************************************
//
//	File:		Query.h
//
//	Description:	Client Query data structure 
//	
//	Copyright 1994-96, Be Incorporated
//
//******************************************************************************/


#ifndef	_QUERY_H
#define	_QUERY_H

#ifndef	_MESSAGE_H
#include "Message.h"
#endif

#ifndef _STORAGE_DEFS_H
#include "StorageDefs.h"
#endif

/*-----------------------------------------------------------------*/

typedef enum {
	B_INVALID_OP = 0,
	B_EQ,
	B_GT,
	B_GE,
	B_LT,
	B_LE,
	B_NE,
	B_AND = 0x101,
	B_OR,
	B_NOT,
	B_ALL,
	_B_RESERVED_OP_ = 0x100000}  query_op;

/*-----------------------------------------------------------------*/

class	BDatabase;
class	BTable;
class   BResList;

/*-----------------------------------------------------------------*/

#define	B_RECORD_ADDED		'clra'	
#define	B_RECORD_MODIFIED	'clrm'	
#define	B_RECORD_REMOVED	'clrr'	

/*-----------------------------------------------------------------*/

class	BQuery : public BObject {
	B_DECLARE_CLASS_INFO(BObject);

	friend		BDatabase;
public:
				BQuery(bool live = FALSE);
				~BQuery();	
		long		Fetch();
		long		FetchOne();
		long		CountRecordIDs();
		record_id	RecordIDAt(long i);
		void		AddTable(BTable *a_table);
		void		AddTree(BTable *a_table);
		long		CountTables();
		BDatabase*	Database();
		void		SetDatabase(BDatabase* db);
		BTable*		TableAt(long idx);
		bool		HasRecordID(record_id id);
		bool		IsLive();
		char		*ToFlat(long *asize);
		void		FromFlat(char *p);
		long		calc_size();

		void		PrintToStream();	
		void		Clear();
		void		PushField(char *name);
		void		PushOp(query_op op);
		void		PushArg(long value);
		void		PushArg(char *string);
		void		PushDate(double time);
		void		PushFieldName(char *field_name);
virtual	void		MessageReceived(BMessage *a_message);
		bool		RunOn(record_id id);
		void		AddRecordID(record_id id);

private:
		BResList	*ResList();
		long		add_any(void *data, long size, long atype);
		BMessage	*Query2Message();

private:
#define	_MAX_ARG_		32
#define	_MAX_QTABLE_	128

		BDatabase	*target_database;
		BResList	*res_list;
		long		table_list[_MAX_QTABLE_];
		long		table_count;
		void		*arg[_MAX_ARG_];
		long		type[_MAX_ARG_];
		long		arg_count;
		long		client_token;
		long		server_token;
		char		pers;
		char		did_run;
		BMessage	*the_message;
};

inline	BDatabase*	BQuery::Database()		{ return(target_database); }
inline	void		BQuery::SetDatabase(BDatabase*	db)
					{ target_database = db; }

/*-----------------------------------------------------------------*/		

void		update_query(BMessage *a_message);

/*-----------------------------------------------------------------*/

#define	B_FIELD_NAME	0x01
#define	B_STRING_ARG	0x02
#define	B_LONG_ARG		0x03
#define	B_OP			0x04
#define	B_BOOL			0x05
#define	B_ALWAYS_NO		0x06
#define	B_VECTOR		0x07
#define	B_DATE_ARG		0x08

/*-----------------------------------------------------------------*/

#define	B_FIRST_CMP		0x01
#define	B_LAST_CMP		0x06

/*-----------------------------------------------------------------*/

#endif
