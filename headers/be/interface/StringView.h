//******************************************************************************
//
//	File:		StringView.h
//
//	Description:	A String text view.
//
//	Copyright 1992-96, Be Incorporated
//
//******************************************************************************

#ifndef _STRING_VIEW_H
#define _STRING_VIEW_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef _VIEW_H
#include "View.h"
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

class BStringView : public BView
{

public:
					BStringView(BRect bounds,
								const char *name, 
								const char *text,
								ulong resizeFlags =
									B_FOLLOW_LEFT | B_FOLLOW_TOP,
								ulong flags = B_WILL_DRAW);
virtual 			~BStringView();

		void		SetText(const char *text);
		const char	*Text() const;
		void		SetAlignment(alignment flag);
		alignment	Alignment() const;

virtual	void		Draw(BRect bounds);

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
