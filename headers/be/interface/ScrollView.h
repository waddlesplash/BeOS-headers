//******************************************************************************
//
//	File:		ScrollView.h
//
//	Description:	auto-scrollbar(s) and bordered view class interface
//
//	Copyright 1993-94, Be Incorporated
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
#include <support/ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BScrollView : public BView {
	DECLARE_CLASS_INFO(BView);

public:
					BScrollView(const char *name,
								BView *target,
								ulong resizeMask = FOLLOW_LEFT_TOP,
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

		BRect		CalcFrame(BView *, bool, bool, bool) const;
		long		ModFlags(long, bool);

		BView		*the_view;
		BScrollBar	*fHSB;	
		BScrollBar	*fVSB;	
		bool		fFramed;
};

//------------------------------------------------------------------------------

#endif
