/*****************************************************************************

     File:			PictureButton.h

     Copyright (c) 1994-96 by Be Incorporated.  All Rights Reserved.

*****************************************************************************/

#ifndef	_PICTURE_BUTTON_H
#define	_PICTURE_BUTTON_H

#ifndef _PICTURE_H
#include <Picture.h>
#endif
#ifndef _CONTROL_H
#include <Control.h>
#endif

enum {
	B_ONE_STATE_BUTTON,
	B_TWO_STATE_BUTTON
};

//------------------------------------------------------------------------------

class BPictureButton : public BControl {
	B_DECLARE_CLASS_INFO(BControl);

public:
					BPictureButton(BRect frame, 
								   const char* name, 
								   BPicture *off, 			   
								   BPicture *on,
								   BMessage *message, 
								   ulong behavior = B_ONE_STATE_BUTTON,
								   ulong resizeMask =
										B_FOLLOW_LEFT | B_FOLLOW_TOP, 
								   ulong flags = B_WILL_DRAW); 
virtual				~BPictureButton();

virtual	void		Draw(BRect updateRect);
virtual	void		MouseDown(BPoint where);

virtual	void		SetEnabledOn(BPicture *on);
virtual	void		SetEnabledOff(BPicture *off);
virtual	void		SetDisabledOn(BPicture *on);
virtual	void		SetDisabledOff(BPicture *off);

virtual	void		SetBehavior(ulong behavior);
		ulong		Behavior() const;

private:
		void		Redraw();

		BPicture	*fEnabledOff;
		BPicture	*fEnabledOn;
		BPicture	*fDisabledOff;
		BPicture	*fDisabledOn;
		bool		fOutlined;
		ulong		fBehavior;
};

//------------------------------------------------------------------------------

#endif
