//******************************************************************************
//
//	File:		Rect.h
//
//	Description:	BRect class header.
//	
//	Copyright 1993-94, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_RECT_H
#define	_RECT_H

#ifndef _SUPPORT_DEFS_H
#include <support/SupportDefs.h>
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
		BRect(const BRect &);
		BRect(long l, long t, long r, long b);
		BRect(BPoint leftTop, BPoint rightBottom);

		// assignment
		BRect		&operator=(const BRect &from);
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
		void		InsetBy(BPoint);
		void		InsetBy(long dx, long dy);
		void		OffsetBy(BPoint);
		void		OffsetBy(long dx, long dy);
		void		OffsetTo(BPoint);
		void		OffsetTo(long x, long y);

		// comparison
		bool		operator==(BRect) const;
		bool		operator!=(BRect) const;

		// intersection and union
		BRect		operator&(BRect) const;
		BRect		operator|(BRect) const;

		// utilities
		bool		Intersects(BRect r) const;
		bool		IsValid() const;
		long		Width() const;
		long		Height() const;
		bool		Contains(BPoint) const;
		bool		Contains(BRect) const;
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

inline BRect::BRect(const BRect &r)
{
	left = r.left;
	top = r.top;
	right = r.right;
	bottom = r.bottom;
}

inline BRect::BRect(BPoint leftTop, BPoint rightBottom)
{
	left = leftTop.x;
	top = leftTop.y;
	right = rightBottom.x;
	bottom = rightBottom.y;
}

inline BRect &BRect::operator=(const BRect& from)
{
	// don't need to worry about "this==from"
	left = from.left;
	top = from.top;
	right = from.right;
	bottom = from.bottom;
	return *this;
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
