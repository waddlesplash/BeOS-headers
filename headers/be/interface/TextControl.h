//******************************************************************************
//
//	File:		TextControl.h
//
//	Description:	A simple text widget that also behaves like a control
//
//	Copyright 1996, Be Incorporated
//
//******************************************************************************

#ifndef	_TEXT_CONTROL_H
#define	_TEXT_CONTROL_H

#ifndef _CONTROL_H
#include "Control.h"
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

class _BTextInput_;

//------------------------------------------------------------------------------

class BTextControl : public BControl {
	B_DECLARE_CLASS_INFO(BControl);

public:
					BTextControl(BRect frame,
								const char *name,
								const char *label, 
								const char *initial_text, 
								BMessage *message,
								ulong resizeMask = B_FOLLOW_LEFT | B_FOLLOW_TOP,
								ulong flags = B_WILL_DRAW); 
virtual				~BTextControl();

virtual	void		SetText(const char *text);
		const char	*Text() const;
virtual	void		SetLabel(const char *text);
		const char	*Label() const;

virtual	void		SetAlignment(alignment label, alignment text);
		void		GetAlignment(alignment *label, alignment *text) const;
virtual	void		SetDivider(float dividing_line);
		float		Divider() const;

		
		// overrides
virtual	void		Draw(BRect updateRect);
virtual	void		MouseDown(BPoint where);
virtual	void		AttachedToWindow();
virtual	void		MakeFocus(bool focusState = TRUE);
virtual	void		SetEnabled(bool state);

protected:
		void		GoToNext();
		void		GoToPrevious();

private:
friend	class _BTextInput_;

		void			CommitValue();
		rgb_color		disable_color(rgb_color);
		rgb_color		enable_color(rgb_color);

		_BTextInput_	*fText;
		char			*fLabel;
		alignment		fLabelAlign;
		float			fDivider;
		float			fLineHeight;
};


//------------------------------------------------------------------------------

#endif
