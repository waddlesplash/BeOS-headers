//******************************************************************************
//
//	File:		ScrollView.h
//
//	Description:	auto-scrollbar(s) and bordered view class interface
//
//	Copyright 1993-97, Be Incorporated
//
//******************************************************************************
 

#ifndef	_SCROLL_VIEW_H
#define	_SCROLL_VIEW_H

#include <ScrollBar.h>
#include <View.h>

/* --------------------------------------------------------------------- */

class BScrollView : public BView {

public:
						BScrollView(const char *name,
								BView *target,
								uint32 resizeMask = B_FOLLOW_LEFT |
													B_FOLLOW_TOP,
								uint32 flags = 0,
								bool horizontal = FALSE,
								bool vertical = FALSE, 
								border_style border = B_FANCY_BORDER);
						BScrollView(BMessage *data);
virtual					~BScrollView();
static	BScrollView		*Instantiate(BMessage *data);
virtual	status_t		Archive(BMessage *data, bool deep = true) const;

virtual	void			Draw(BRect updateRect);
virtual	void			AttachedToWindow();
		BScrollBar		*ScrollBar(orientation flag) const;

virtual	void			SetBorder(border_style border);
		border_style	Border() const;

virtual	status_t		SetBorderHighlighted(bool state);
		bool			IsBorderHighlighted() const;

virtual void			MessageReceived(BMessage *msg);
virtual	void			MouseDown(BPoint pt);
virtual void			WindowActivated(bool state);
virtual	void			MouseUp(BPoint pt);
virtual	void			MouseMoved(BPoint pt, uint32 code, const BMessage *msg);
virtual	void			DetachedFromWindow();
virtual	void			AllAttached();
virtual	void			AllDetached();
virtual	void			FrameMoved(BPoint new_position);
virtual	void			FrameResized(float new_width, float new_height);

virtual BHandler		*ResolveSpecifier(BMessage *msg,
										int32 index,
										BMessage *specifier,
										int32 form,
										const char *property);
virtual status_t		Perform(uint32 d, void *arg);

private:

friend class BView;

virtual	void			_ReservedScrollView1();
virtual	void			_ReservedScrollView2();
virtual	void			_ReservedScrollView3();
virtual	void			_ReservedScrollView4();

		BScrollView		&operator=(const BScrollView &);

static	BRect			CalcFrame(BView *, bool, bool, border_style);
		int32			ModFlags(int32, border_style);
		void			InitObject();

		BView			*fTarget;
		BScrollBar		*fHSB;	
		BScrollBar		*fVSB;	
		border_style	fBorder;
		uint32			_reserved[4];

		bool			fHighlighted;
};

#endif
