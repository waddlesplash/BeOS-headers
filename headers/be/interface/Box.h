//******************************************************************************
//
//	File:		Box.h
//
//	Description:	client framed view class.
//
//	Copyright 1993-97, Be Incorporated
//
//******************************************************************************

#pragma once

#ifndef _BOX_H
#define _BOX_H

#include <View.h>

class BBox : public BView
{
public:
						BBox(BRect bounds,
							const char *name = NULL,
							uint32 resizeFlags = B_FOLLOW_LEFT | B_FOLLOW_TOP,
							uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS |
											B_NAVIGABLE_JUMP,
							border_style border = B_FANCY_BORDER);

						BBox(BMessage *data);
virtual 				~BBox(void);
static	BBox			*Instantiate(BMessage *data);
virtual	status_t		Archive(BMessage *data, bool deep = true) const;
virtual	void			SetBorder(border_style style);
		border_style	Border() const;

		const char		*Label() const;
		void			SetLabel(const char *label);
virtual	void			Draw(BRect bounds);
virtual	void			AttachedToWindow();
virtual	void			DetachedFromWindow();
virtual	void			AllAttached();
virtual	void			AllDetached();
virtual void			FrameResized(float new_width, float new_height);
virtual void			MessageReceived(BMessage *msg);
virtual	void			MouseDown(BPoint pt);
virtual	void			MouseUp(BPoint pt);
virtual	void			WindowActivated(bool state);
virtual	void			MouseMoved(BPoint pt, uint32 code, const BMessage *msg);
virtual	void			FrameMoved(BPoint new_position);

virtual BHandler		*ResolveSpecifier(BMessage *msg,
										int32 index,
										BMessage *specifier,
										int32 form,
										const char *property);

virtual status_t		Perform(uint32 d, void *arg);

private:

virtual	void			_ReservedBox1();
virtual	void			_ReservedBox2();

		BBox			&operator=(const BBox &);

		void			InitObject(BMessage *data = NULL);
		void			DrawPlain();
		void			DrawFancy();

		char			*fLabel;
		BRect			fBounds;
		border_style	fStyle;
		uint32			_reserved[2];
};

#endif
