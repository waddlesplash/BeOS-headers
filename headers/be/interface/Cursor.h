//******************************************************************************
//
//	File:		Cursor.h
//
//	Copyright 1994, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef _CURSOR_H
#define _CURSOR_H

#ifndef _OBJECT_H
#include <support/Object.h>
#endif
#ifndef _POINT_H
#include "Point.h"
#endif
#ifndef _BITMAP_H
#include "Bitmap.h"
#endif

class BCursor : public BObject
{
	DECLARE_CLASS_INFO(BObject);

public:
		void	Show();
		void	Hide();
		void	Obscure();
		bool	IsHidden();
		
		void	SetBitmap(BBitmap *bitmap, BPoint hotSpot);
		void	SetDefault();

private:
friend BApplication;

virtual			~BCursor();
				BCursor();
};

BCursor *the_cursor;

#endif
