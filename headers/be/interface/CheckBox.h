//******************************************************************************
//
//	File:		CheckBox.h
//
//	Description:	CheckBox class.
//
//	Copyright 1992-96, Be Incorporated
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
#include <ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BCheckBox : public BControl {
	B_DECLARE_CLASS_INFO(BControl);

public:
				BCheckBox(	BRect frame,
							const char *name,
							const char *label,
							BMessage *message,
							ulong resizeMask = B_FOLLOW_LEFT | B_FOLLOW_TOP, 
							ulong flags = B_WILL_DRAW); 

virtual	void	Draw(BRect updateRect);
virtual	void	MouseDown(BPoint where);

//------------------------------------------------------------------------------

private:
	bool		fOutlined;
	
};


//------------------------------------------------------------------------------

#endif
