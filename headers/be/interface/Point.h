//******************************************************************************
//
//	File:		Point.h
//
//	Description:	BPoint class header.
//	
//	Copyright 1993-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_POINT_H
#define	_POINT_H

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

class BRect;

class BPoint {

public:
		float x;
		float y;

		// constructors
		BPoint();
		BPoint(float X, float Y);
		BPoint(const BPoint& pt);
		
		// assignment
		BPoint		&operator=(const BPoint &from);
		void		Set(float X, float Y);

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

extern const BPoint B_ORIGIN;

inline BPoint::BPoint()
{
}

inline BPoint::BPoint(float X, float Y)
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

inline void BPoint::Set(float X, float Y)
{
	x = X;
	y = Y;
}

#endif
