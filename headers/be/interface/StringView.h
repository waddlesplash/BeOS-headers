//******************************************************************************
//
//	File:		StringView.h
//
//	Description:	A String text view.
//
//	Copyright 1992-94, Be Incorporated
//
//******************************************************************************

#ifndef _STING_VIEW_H
#define _STING_VIEW_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef _VIEW_H
#include "View.h"
#endif
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

class BStringView : public BView
{
	DECLARE_CLASS_INFO(BView);

public:
					BStringView(BRect bounds,
								const char *name, 
								const char *text,
								ulong resizeFlags = FOLLOW_LEFT_TOP,
								ulong flags = WILL_DRAW);
virtual 			~BStringView();
virtual void		AttachedToWindow();

		void		SetText(const char *text);
		const char	*Text() const;
		void		SetAlignment(alignment flag);
		alignment	Alignment() const;

virtual	void		Draw(BRect bounds);
virtual long		ResourceDataLength() const;
virtual void		GetResourceData(void *buf) const;
virtual void		SetResourceData(void *buf, long len);

// ----------------------------------------------------------------

private:
		char		*fText;
		alignment	fAlign;
};

inline alignment BStringView::Alignment() const
	{ return fAlign; }

inline const char *BStringView::Text() const
	{ return fText; }

#endif
