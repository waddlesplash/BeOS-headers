//******************************************************************************
//
//	File:			Picture.h
//
//	Description:	Client picture class.
//
//	Copyright 1995-96, Be Incorporated. All Rights Reserved
//
//******************************************************************************

#ifndef	_PICTURE_H
#define	_PICTURE_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef	_RECT_H
#include "Rect.h"
#endif
#ifndef	_OBJECT_H
#include <Object.h>
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

//------------------------------------------------------------------------------
class	BView;
//------------------------------------------------------------------------------

class BPicture : public BObject {
	B_DECLARE_CLASS_INFO(BObject);

public:
				BPicture();
				BPicture(const BPicture &original);
				BPicture(void *data, long size);

virtual			~BPicture();	
		void	*Data() const;
		long	DataSize() const;
		
private:
		friend class BView;

		void	set_fields(long token, void *data, long size);
		long	server_token;
		void	*server_data;
		long	server_data_size;
};

//------------------------------------------------------------------------------

#endif
