//******************************************************************************
//
//	File:		CheckBox.h
//
//	Description:	CheckBox class.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1992-93, Be Incorporated
//
//******************************************************************************

#ifndef	_CHECK_BOX_H
#define	_CHECK_BOX_H

#ifndef _CONTROL_H
#include "Control.h"
#endif

//------------------------------------------------------------------------------

class BCheckBox : public BControl {
public:
			BCheckBox(BRect *frame, char *name, char *label,
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

inline char		*BCheckBox::ClassName() { return "BCheckBox"; };

//------------------------------------------------------------------------------

#endif
