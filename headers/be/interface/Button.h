//******************************************************************************
//
//	File:		Button.h
//
//	Description:	button class.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1992-93, Be Incorporated
//
//******************************************************************************

#ifndef	_BUTTON_H
#define	_BUTTON_H

#ifndef _CONTROL_H
#include "Control.h"
#endif

//------------------------------------------------------------------------------

class BButton : public BControl {
public:
			BButton(BRect *frame, char *name, char *label, 
				long command = -1, 
				ulong resizeMask = FOLLOW_LEFT_TOP, 
				ulong flags = WILL_DRAW); 
virtual	char		*ClassName();

virtual	void		Draw(BRect *updateRect);
virtual	void		MouseDown(BPoint where);
};

inline char		*BButton::ClassName() { return "BButton"; };

//------------------------------------------------------------------------------

#endif
