//******************************************************************************
//
//	File:		ScrollBar.h
//
//	Description:	ScrollBar control class.
//
//	Copyright 1992-96, Be Incorporated
//
//******************************************************************************


#ifndef	_SCROLL_BAR_H
#define	_SCROLL_BAR_H

#ifndef _VIEW_H
#include "View.h"
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

class BApplication;

//------------------------------------------------------------------------------

class BScrollBar : public BView {
	B_DECLARE_CLASS_INFO(BView);

public:
					BScrollBar(	BRect frame,
								const char *name,
								BView *target,
								long min,
								long max,
								orientation direction);
virtual				~BScrollBar();
			
		void		SetValue(long value);
		long		Value() const;
virtual	void		ValueChanged(long newValue);

		void		SetRange(long min, long max);
		void		GetRange(long *min, long *max) const;
		void		SetSteps(long smallStep, long largeStep);
		void		GetSteps(long *smallStep, long *largeStep) const;
		void		SetTarget(BView *target);
		void		SetTarget(char *targetName);
		BView		*Target() const;
		orientation	Orientation() const;

//------------------------------------------------------------------------------

private:

friend BWindow;
friend BApplication;

		long		fMin;
		long		fMax;
		long		fSmallStep;
		long		fLargeStep;
		long		fValue;
		BView*		fTarget;	
		orientation	fOrientation;
		char		*fTargetName;
};

inline orientation	BScrollBar::Orientation() const 
	{ return fOrientation; }

inline BView		*BScrollBar::Target() const
	{ return fTarget; }

//------------------------------------------------------------------------------

#endif
