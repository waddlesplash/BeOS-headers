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

#define B_V_SCROLL_BAR_WIDTH	14.0
#define B_H_SCROLL_BAR_HEIGHT	14.0

//------------------------------------------------------------------------------

class BScrollBar : public BView {

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
		void		SetProportion(float);
		float		Proportion() const;
virtual	void		ValueChanged(long newValue);

		void		SetRange(long min, long max);
		void		GetRange(long *min, long *max) const;
		void		SetSteps(long smallStep, long largeStep);
		void		GetSteps(long *smallStep, long *largeStep) const;
		void		SetTarget(BView *target);
		void		SetTarget(const char *targetName);
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
		float		fProportion;
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
