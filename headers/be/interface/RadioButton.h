//******************************************************************************
//
//	File:		RadioButton.h
//
//	Description:	radio button class.
//
//	Copyright 1992-97, Be Incorporated
//
//******************************************************************************


#ifndef	_RADIO_BUTTON_H
#define	_RADIO_BUTTON_H

#include <Control.h>
#include <Window.h>

//---------------------------------------------------------------------------

class BRadioButton : public BControl {

public:
						BRadioButton(BRect frame,
								const char *name,
								const char *label,
								BMessage *message,
								uint32 resizeMask = B_FOLLOW_LEFT | B_FOLLOW_TOP,
								uint32 flags = B_WILL_DRAW | B_NAVIGABLE); 

						BRadioButton(BMessage *data);
virtual					~BRadioButton();

static	BRadioButton	*Instantiate(BMessage *data);
virtual	status_t		Archive(BMessage *data, bool deep = true) const;

virtual	void			Draw(BRect updateRect);
virtual	void			MouseDown(BPoint where);
virtual	void			AttachedToWindow();
virtual	void			KeyDown(const char *bytes, int32 numBytes);
virtual	void			SetValue(int32 value);
virtual	void			GetPreferredSize(float *width, float *height);
virtual void			ResizeToPreferred();
virtual	status_t		Invoke(BMessage *msg = NULL);

virtual void			MessageReceived(BMessage *msg);
virtual void			WindowActivated(bool state);
virtual	void			MouseUp(BPoint pt);
virtual	void			MouseMoved(BPoint pt, uint32 code, const BMessage *msg);
virtual	void			DetachedFromWindow();
virtual	void			FrameMoved(BPoint new_position);
virtual	void			FrameResized(float new_width, float new_height);

virtual BHandler		*ResolveSpecifier(BMessage *msg,
										int32 index,
										BMessage *specifier,
										int32 form,
										const char *property);
virtual status_t		Perform(uint32 d, void *arg);

private:

virtual	void			_ReservedRadioButton1();
virtual	void			_ReservedRadioButton2();

		BRadioButton	&operator=(const BRadioButton &);

		bool			fOutlined;
		uint32			_reserved[2];
};

#endif
