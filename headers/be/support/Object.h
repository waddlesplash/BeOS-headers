//******************************************************************************
//
//	File:		Object.h
//
//	Description:	top object 
//
//	Copyright 1992-96, Be Incorporated
//
//******************************************************************************

#ifndef	_OBJECT_H
#define	_OBJECT_H

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BObject {
	B_DECLARE_ROOT_CLASS_INFO();
public:
				BObject();
virtual			~BObject();	
};

//------------------------------------------------------------------------------

#endif
