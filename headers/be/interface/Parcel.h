//******************************************************************************
//
//	File:		Parcel.h
//
//	Description:	Client dragging object.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1992, Be Incorporated
//
//******************************************************************************

#ifndef	_PARCEL_H
#define	_PARCEL_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef	_LIST_H
#include <sys/List.h>
#endif
#ifndef	_OBJECT_H
#include <sys/Object.h>
#endif

class BSession;
       
//------------------------------------------------------------------------------

class BParcel : public BObject {

public:
			BParcel();
virtual			~BParcel();	
virtual	char		*ClassName();

	bool		AddItem(void *data, long length, long type);
	bool		GetItem(long type, long index, void **ptr,
				long *length, long *type);
	long		CountItems(long type);
	bool		HasType(long type);

//------------------------------------------------------------------------------
friend class BApplication;

private:
	void		write_yourself(BSession *the_session);

	BList*		types;
	BList*		sizes;
	BList*		datas;
};

inline char		*BParcel::ClassName() { return "BParcel"; };

//------------------------------------------------------------------------------

#endif
