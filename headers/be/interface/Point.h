//******************************************************************************
//
//	File:		Point.h
//
//	Description:	BPoint class header.
//	
//	Written by:	Steve Horowitz
//
//	Copyright 1993, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_POINT_H
#define	_POINT_H

#ifndef _BE_DEFS_H
#include <sys/BeDefs.h>
#endif

class BPoint {

public:
	long x;
	long y;

	// constructors
	BPoint();
	BPoint(long X, long Y);
	BPoint(const BPoint& pt);
	
	// assignment
	void		Set(long X, long Y);

	// utility to print in text form
	void		PrintToStream();
	
	// arithmetic
	BPoint		operator+(const BPoint&) const;
	BPoint		operator-(const BPoint&) const;
	BPoint&		operator+=(const BPoint&);
	BPoint&		operator-=(const BPoint&);

	// relational
	bool		operator!=(const BPoint&) const;
	bool		operator==(const BPoint&) const;
};


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

inline void BPoint::Set(long X, long Y)
{
	x = X;
	y = Y;
}

#endif
