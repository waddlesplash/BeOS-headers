//******************************************************************************
//
//	File:		ScrollView.h
//
//	Description:	auto-scrollbar(s) and bordered view class interface
//
//	Written by:	Eric Knight
//
//	Copyright 1993, Be Incorporated
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

//------------------------------------------------------------------------------

class BScrollView : public BView {

public:
			BScrollView(char *name, BView *target, 
				    ulong resizeMask = FOLLOW_LEFT_TOP,
				    ulong flags = 0, bool horizontal = FALSE, 
				    bool vertical = FALSE, 
				    bool bordered = TRUE);
virtual			~BScrollView();
virtual	char		*ClassName();

virtual	void		Draw(BRect *updateRect);
	BScrollBar	*ScrollBar(orientation flag);

//------------------------------------------------------------------------------
friend class BView;

private:
	BRect*		ExpandRect(BRect*, bool, bool, bool);
	void		RevertRect(BRect*, bool, bool, bool);
	long		ModFlags(long, bool);

	BView		*the_view;
	BScrollBar	*fHSB;	
	BScrollBar	*fVSB;	
};

inline char		*BScrollView::ClassName() { return "BScrollView"; };

//------------------------------------------------------------------------------

#endif
