//******************************************************************************
//
//	File:		RadioButton.h
//
//	Description:	radio button class.
//
//	Copyright 1992-96, Be Incorporated
//
//******************************************************************************

#ifndef	_RADIO_BUTTON_H
#define	_RADIO_BUTTON_H

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

class BRadioButton : public BControl {

public:
				BRadioButton(	BRect frame,
								const char *name,
								const char *label,
								BMessage *message,
								ulong resizeMask = B_FOLLOW_LEFT | B_FOLLOW_TOP,
								ulong flags = B_WILL_DRAW | B_NAVIGABLE); 

virtual	void	Draw(BRect updateRect);
virtual	void	MouseDown(BPoint where);
virtual	void	AttachedToWindow();
virtual	void	KeyDown(ulong key);
virtual	void	SetValue(long value);

//------------------------------------------------------------------------------

private:
	bool		fOutlined;
	
};

#endif
