//******************************************************************************
//
//	File:		StringView.h
//
//	Description:	A String text view.
//
//	Copyright 1992-97, Be Incorporated
//
//******************************************************************************


#ifndef _STRING_VIEW_H
#define _STRING_VIEW_H

#include <InterfaceDefs.h>
#include <View.h>

class BStringView : public BView
{

public:
					BStringView(BRect bounds,
								const char *name, 
								const char *text,
								uint32 resizeFlags =
									B_FOLLOW_LEFT | B_FOLLOW_TOP,
								uint32 flags = B_WILL_DRAW);
					BStringView(BMessage *data);
virtual 			~BStringView();
static	BStringView	*Instantiate(BMessage *data);
virtual	status_t	Archive(BMessage *data, bool deep = true) const;

		void		SetText(const char *text);
		const char	*Text() const;
		void		SetAlignment(alignment flag);
		alignment	Alignment() const;

virtual	void		AttachedToWindow();
virtual	void		Draw(BRect bounds);

virtual void		MessageReceived(BMessage *msg);
virtual	void		MouseDown(BPoint pt);
virtual	void		MouseUp(BPoint pt);
virtual	void		MouseMoved(BPoint pt, uint32 code, const BMessage *msg);
virtual	void		DetachedFromWindow();
virtual	void		FrameMoved(BPoint new_position);
virtual	void		FrameResized(float new_width, float new_height);

virtual BHandler	*ResolveSpecifier(BMessage *msg,
									int32 index,
									BMessage *specifier,
									int32 form,
									const char *property);
virtual status_t	Perform(uint32 d, void *arg);

private:

virtual	void		_ReservedStringView1();
virtual	void		_ReservedStringView2();
virtual	void		_ReservedStringView3();

		BStringView	&operator=(const BStringView &);

		char		*fText;
		alignment	fAlign;
		uint32		_reserved[3];
};

#endif
