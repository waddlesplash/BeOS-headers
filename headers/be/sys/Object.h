//******************************************************************************
//
//	File:		Object.h
//
//	Description:	top object 
//
//	Written by:	Benoit Schillings
//
//	Copyright 1992-3, Be Incorporated
//
//******************************************************************************

#ifndef	_OBJECT_H
#define	_OBJECT_H

#ifndef _BE_DEFS_H
#include "BeDefs.h"
#endif

//------------------------------------------------------------------------------

class BObject {
public:
			BObject();
virtual			~BObject();	
virtual	char		*ClassName();
	bool		IsInstanceOf(char* objectType);
};

inline char		*BObject::ClassName() { return "BObject"; };

//------------------------------------------------------------------------------

#endif
