//******************************************************************************
//
//	File:		Button.h
//
//	Description:	button class.
//
//	Copyright 1992-94, Be Incorporated
//
//******************************************************************************

#ifndef	_BUTTON_H
#define	_BUTTON_H

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

class BButton : public BControl {
	DECLARE_CLASS_INFO(BControl);

public:
				BButton(BRect frame,
						const char *name,
						const char *label, 
						ulong command = 'BUTN', 
						ulong resizeMask = FOLLOW_LEFT_TOP, 
						ulong flags = WILL_DRAW); 

virtual	void	Draw(BRect updateRect);
virtual	void	MouseDown(BPoint where);
};


//------------------------------------------------------------------------------

#endif
