//******************************************************************************
//
//	File:		Point.h
//
//	Description:	BPoint class header.
//	
//	Copyright 1993, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_POINT_H
#define	_POINT_H

#ifndef _SUPPORT_DEFS_H
#include <support/SupportDefs.h>
#endif

class BRect;

class BPoint {

public:
		long x;
		long y;

		// constructors
		BPoint();
		BPoint(long X, long Y);
		BPoint(const BPoint& pt);
		
		// assignment
		BPoint		&operator=(const BPoint &from);
		void		Set(long X, long Y);

		void		ConstrainTo(BRect rect);

		// utility to print in text form
		void		PrintToStream() const;
			
		// arithmetic
		BPoint		operator+(const BPoint&) const;
		BPoint		operator-(const BPoint&) const;
		BPoint&		operator+=(const BPoint&);
		BPoint&		operator-=(const BPoint&);

		// relational
		bool		operator!=(const BPoint&) const;
		bool		operator==(const BPoint&) const;
};

extern const BPoint ORIGIN;

inline BPoint::BPoint()
{
}

inline BPoint::BPoint(long X, long Y)
{
	x = X;
	y = Y;
}

inline BPoint::BPoint(const BPoint& pt)
{
	x = pt.x;
	y = pt.y;
}

inline BPoint &BPoint::operator=(const BPoint& from)
{
	// don't need to worry about "this==from"
	x = from.x;
	y = from.y;
	return *this;
}

inline void BPoint::Set(long X, long Y)
{
	x = X;
	y = Y;
}

#endif
