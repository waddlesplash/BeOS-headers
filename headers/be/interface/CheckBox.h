//******************************************************************************
//
//	File:		CheckBox.h
//
//	Description:	CheckBox class.
//
//	Copyright 1992-94, Be Incorporated
//
//******************************************************************************

#ifndef	_CHECK_BOX_H
#define	_CHECK_BOX_H

#ifndef _CONTROL_H
#include "Control.h"
#endif
#ifndef _WINDOW_H
#include "Window.h"
#endif
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BCheckBox : public BControl {
	DECLARE_CLASS_INFO(BControl);

public:
				BCheckBox(	BRect frame,
							const char *name,
							const char *label,
							ulong command = 'CBOX', 
							ulong resizeMask = FOLLOW_LEFT_TOP, 
							ulong flags = WILL_DRAW); 

virtual	void	Draw(BRect updateRect);
virtual	void	MouseDown(BPoint where);

//------------------------------------------------------------------------------

private:
	bool		fOutlined;
	
};


//------------------------------------------------------------------------------

#endif
