//******************************************************************************
//
//	File:		Rect.h
//
//	Description:	BRect class header.
//	
//	Written by:	Steve Horowitz
//
//	Copyright 1993, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_RECT_H
#define	_RECT_H

#ifndef _BE_DEFS_H
#include <sys/BeDefs.h>
#endif
#ifndef _POINT_H
#include "Point.h"
#endif

class BRect {

public:
	long		left;
	long		top;
	long		right;
	long		bottom;

	// constructors
	BRect();
	BRect(const BRect *);
	BRect(long l, long t, long r, long b);
	BRect(BPoint leftTop, BPoint rightBottom);

	// assignment
	void		Set(long l, long t, long r, long b);

	// utility to print in text form
	void		PrintToStream() const;

	// BPoint selectors
	BPoint		LeftTop() const;
	BPoint		RightBottom() const;
	BPoint		LeftBottom() const;
	BPoint		RightTop() const;

	// BPoint setters
	void		SetLeftTop(const BPoint);
	void		SetRightBottom(const BPoint);
	void		SetLeftBottom(const BPoint);
	void		SetRightTop(const BPoint);

	// transformation
	void		InsetBy(long dx, long dy);
	void		OffsetBy(long dx, long dy);
	void		OffsetTo(BPoint);
	void		OffsetTo(long x, long y);

	// comparison
	bool		operator==(const BRect&) const;
	bool		operator!=(const BRect&) const;

	// intersection and union
	BRect		operator&(const BRect&) const;
	BRect		operator|(const BRect&) const;

	// utilities
	bool		Intersects(const BRect* r) const;
	bool		IsValid() const;
	long		Width() const;
	long		Height() const;
	bool		Contains(BPoint) const;
	bool		Contains(const BRect *) const;
	void		ConstrainPoint(BPoint *);
};


//------------------------------------------------------------------------------

inline BPoint BRect::LeftTop() const
{
	return(*((BPoint*)&left));
}

inline BPoint BRect::RightBottom() const
{
	return(*((BPoint*)&right));
}

inline BPoint BRect::LeftBottom() const
{
	return(BPoint(left, bottom));
}

inline BPoint BRect::RightTop() const
{
	return(BPoint(right, top));
}

inline BRect::BRect()
{
	// make initial rect invalid
	top = left = 0;
	bottom = right = -1;
}

inline BRect::BRect(long l, long t, long r, long b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}

inline BRect::BRect(const BRect* r)
{
	left = r->left;
	top = r->top;
	right = r->right;
	bottom = r->bottom;
}

inline BRect::BRect(BPoint leftTop, BPoint rightBottom)
{
	left = leftTop.x;
	top = leftTop.y;
	right = rightBottom.x;
	bottom = rightBottom.y;
}

inline void BRect::Set(long l, long t, long r, long b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}

inline bool BRect::IsValid() const
{
	if (left <= right && top <= bottom)
		return TRUE;
	else
		return FALSE;
}

inline long BRect::Width() const
{
	return(right - left + 1);
}

inline long BRect::Height() const
{
	return(bottom - top + 1);
}

#endif
