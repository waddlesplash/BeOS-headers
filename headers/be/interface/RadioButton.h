//******************************************************************************
//
//	File:		RadioButton.h
//
//	Description:	radio button class.
//
//	Copyright 1992-94, Be Incorporated
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
#include <support/ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BRadioButton : public BControl {
	DECLARE_CLASS_INFO(BControl);

public:
				BRadioButton(	BRect frame,
								const char *name,
								const char *label,
								ulong command = 'RADO',
								ulong resizeMask = FOLLOW_LEFT_TOP,
								ulong flags = WILL_DRAW); 

virtual	void	Draw(BRect updateRect);
virtual	void	MouseDown(BPoint where);

//------------------------------------------------------------------------------

private:
	bool		fOutlined;
	
};

#endif
