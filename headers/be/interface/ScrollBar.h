//******************************************************************************
//
//	File:		ScrollBar.h
//
//	Description:	ScrollBar control class.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1992-93, Be Incorporated
//
//******************************************************************************


#ifndef	_SCROLL_BAR_H
#define	_SCROLL_BAR_H

#ifndef _VIEW_H
#include "View.h"
#endif

class BApplication;

//------------------------------------------------------------------------------

class BScrollBar : public BView {

public:
			BScrollBar(BRect *frame, char *name, BView *target, 
				   long min, long max, orientation direction);
virtual			~BScrollBar();
virtual	char		*ClassName();
			
	void		SetValue(long value);
	long		Value();
virtual	void		ValueChanged(long newValue);
virtual long		ResourceDataLength();

	void		SetRange(long min, long max);
	void		GetRange(long* min, long* max);
	void		SetTarget(BView *target);
	void		SetTarget(char *targetName);
	orientation Orientation() { return fOrientation; };

virtual void		GetResourceData(void *buf);
virtual void		SetResourceData(void *buf, long len);

//------------------------------------------------------------------------------
friend BWindow;
friend BApplication;

private:
	long		min;
	long		max;
	long		fValue;
	BView*		fTarget;	
	orientation	fOrientation;
	char		*fTargetName;
};

inline char		*BScrollBar::ClassName() { return "BScrollBar"; };

//------------------------------------------------------------------------------

#endif
