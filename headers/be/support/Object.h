//******************************************************************************
//
//	File:		Object.h
//
//	Description:	top object 
//
//	Copyright 1992-94, Be Incorporated
//
//******************************************************************************

#ifndef	_OBJECT_H
#define	_OBJECT_H

#ifndef _SUPPORT_DEFS_H
#include <support/SupportDefs.h>
#endif

#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BObject {
	DECLARE_ROOT_CLASS_INFO();
public:
				BObject();
virtual			~BObject();	
};

//------------------------------------------------------------------------------

#endif
