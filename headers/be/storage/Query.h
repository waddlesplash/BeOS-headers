//******************************************************************************
//
//	File:		Query.h
//
//	Description:	Client Query data structure 
//	
//	Copyright 1994, Be Incorporated
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

typedef long enum {
	EQ = 0x01,
	GT,
	GE,
	LT,
	LE,
	NE,
	AND = 0x101,
	OR,
	NOT }  query_op;

/*-----------------------------------------------------------------*/

class	BDatabase;
class	BTable;
class   BResList;

/*-----------------------------------------------------------------*/

#define	DB_RECORD_ADD		'clra'	
#define	DB_RECORD_MODIFY	'clrm'	
#define	DB_RECORD_REMOVE	'clrr'	

/*-----------------------------------------------------------------*/

class	BQuery : public BObject {
	DECLARE_CLASS_INFO(BObject);

	friend		BDatabase;
public:
		void		BQuery(bool live = FALSE);
		void		~BQuery();	
		long		Fetch();
		long		FetchOne();
		long		CountRefs();
		record_ref	RefAt(long i);
		void		AddTable(BTable *a_table);
		void		AddTree(BTable *a_table);
		long		CountTables();
		BTable*		TableAt(long idx);
		bool		HasRef(long ref);
		bool		IsLive();

		void		PrintToStream();	
		void		Clear();
		void		PushField(char *name);
		void		PushOp(query_op op);
		void		PushArg(long value);
		void		PushArg(char *string);
		void		PushFieldName(char *field_name);
virtual	void		MessageReceived(BMessage *a_message);
		bool		RunOn(record_ref ref);

private:
		BResList	*ResList();
		long		add_any(void *data, long size, long atype);
		BMessage	*Query2Message();

private:
#define	MAX_ARG		32
#define	MAX_QTABLE	128

		BDatabase	*target_database;
		BResList	*res_list;
		long		table_list[MAX_QTABLE];
		long		table_count;
		void		*arg[MAX_ARG];
		long		type[MAX_ARG];
		long		arg_count;
		long		client_token;
		long		server_token;
		char		pers;
		char		did_run;
};

/*-----------------------------------------------------------------*/		

void		update_query(BMessage *a_message);

/*-----------------------------------------------------------------*/

#define	FIELD_NAME	0x01
#define	STRING_ARG	0x02
#define	LONG_ARG	0x03
#define	OP			0x04
#define	BOOL		0x05
#define	ALWAYS_NO	0x06
#define	VECTOR		0x07

/*-----------------------------------------------------------------*/

#define	FIRST_CMP	0x01
#define	LAST_CMP	0x06

/*-----------------------------------------------------------------*/

#endif
