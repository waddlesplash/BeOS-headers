/*******************************************************************************
/
/	File:			Point.h
/
/   Description:    BPoint represents a single x,y coordinate.
/
/	Copyright 1993-98, Be Incorporated, All Rights Reserved
/
/******************************************************************************/

#ifndef	_POINT_H
#define	_POINT_H

#include <BeBuild.h>
#include <SupportDefs.h>

class BRect;

/*----------------------------------------------------------------*/
/*----- BPoint class --------------------------------------------*/

class BPoint {

public:
		float x;
		float y;

		BPoint();
		BPoint(float X, float Y);
		BPoint(const BPoint& pt);
		
		BPoint		&operator=(const BPoint &from);
		void		Set(float X, float Y);

		void		ConstrainTo(BRect rect);

		void		PrintToStream() const;
			
		BPoint		operator+(const BPoint&) const;
		BPoint		operator-(const BPoint&) const;
		BPoint&		operator+=(const BPoint&);
		BPoint&		operator-=(const BPoint&);

		bool		operator!=(const BPoint&) const;
		bool		operator==(const BPoint&) const;
};

extern _IMPEXP_BE const BPoint B_ORIGIN;

/*----------------------------------------------------------------*/
/*----- inline definitions ---------------------------------------*/

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
	x = from.x;
	y = from.y;
	return *this;
}

inline void BPoint::Set(float X, float Y)
{
	x = X;
	y = Y;
}

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/

#endif /* _POINT_H */
