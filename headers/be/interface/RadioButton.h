//******************************************************************************
//
//	File:		RadioButton.h
//
//	Description:	radio button class.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1992-93, Be Incorporated
//
//******************************************************************************

#ifndef	_RADIO_BUTTON_H
#define	_RADIO_BUTTON_H

#ifndef _CONTROL_H
#include "Control.h"
#endif

//------------------------------------------------------------------------------

class BRadioButton : public BControl {

public:
			BRadioButton(BRect *frame, char *name, char *label, 
				     long command = -1,
				     ulong resizeMask = FOLLOW_LEFT_TOP, 
				     ulong flags = WILL_DRAW); 
virtual	char		*ClassName();

virtual	void		Draw(BRect *updateRect);
virtual	void		MouseDown(BPoint where);

//------------------------------------------------------------------------------

private:
	bool		fOutlined;
	
};

inline char		*BRadioButton::ClassName() { return "BRadioButton"; };

#endif
