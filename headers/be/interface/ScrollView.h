//******************************************************************************
//
//	File:		ScrollView.h
//
//	Description:	auto-scrollbar(s) and bordered view class interface
//
//	Copyright 1993-96, Be Incorporated
//
//******************************************************************************
 
#ifndef	_SCROLL_VIEW_H
#define	_SCROLL_VIEW_H

#ifndef _SCROLL_BAR_H
#include "ScrollBar.h"
#endif
#ifndef _VIEW_H
#include "View.h"
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BScrollView : public BView {
	B_DECLARE_CLASS_INFO(BView);

public:
					BScrollView(const char *name,
								BView *target,
								ulong resizeMask = B_FOLLOW_LEFT_TOP,
								ulong flags = 0,
								bool horizontal = FALSE,
								bool vertical = FALSE, 
								bool bordered = TRUE);
virtual				~BScrollView();

virtual	void		Draw(BRect updateRect);
		BScrollBar	*ScrollBar(orientation flag) const;

//------------------------------------------------------------------------------

private:

friend class BView;

static	BRect		CalcFrame(BView *, bool, bool, bool);
		long		ModFlags(long, bool);

		BView		*the_view;
		BScrollBar	*fHSB;	
		BScrollBar	*fVSB;	
		bool		fFramed;
};

//------------------------------------------------------------------------------

#endif
