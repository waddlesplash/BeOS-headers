//******************************************************************************
//
//	File:		Button.h
//
//	Description:	button class.
//
//	Copyright 1992-96, Be Incorporated
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
#include <ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BButton : public BControl {
	B_DECLARE_CLASS_INFO(BControl);

public:
				BButton(BRect frame,
						const char *name,
						const char *label, 
						BMessage *message,
						ulong resizeMask = B_FOLLOW_LEFT | B_FOLLOW_TOP, 
						ulong flags = B_WILL_DRAW); 

virtual	void	Draw(BRect updateRect);
virtual	void	MouseDown(BPoint where);
virtual	void	AttachedToWindow();
virtual	void	KeyDown(ulong key);
virtual void	MakeDefault(bool state);
		bool	IsDefault() const;

private:
		bool	fDrawAsDefault;
};


//------------------------------------------------------------------------------

#endif
