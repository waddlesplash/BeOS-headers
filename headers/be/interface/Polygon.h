//******************************************************************************
//
//	File:		Polygon.h
//
//	Description:	Client polygon class.
//
//	Copyright 1992-93, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_POLYGON_H
#define	_POLYGON_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef	_RECT_H
#include "Rect.h"
#endif
#ifndef	_OBJECT_H
#include <support/Object.h>
#endif
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BPolygon : public BObject {
	DECLARE_CLASS_INFO(BObject);

public:
					BPolygon(BPoint *ptArray, long numPoints);
					BPolygon();
					BPolygon(const BPolygon *poly);
virtual				~BPolygon();	

		BPolygon	&operator=(const BPolygon &from);

		BRect		Frame() const;
		void		AddPoints(const BPoint *ptArray, long numPoints);
		long		CountPoints() const;
		void		MapTo(BRect srcRect, BRect dstRect);
		void		PrintToStream() const;

//------------------------------------------------------------------------------

private:

friend class BView;

		void	compute_bounds();
		void	map_pt(BPoint *, BRect srcRect, BRect dstRect);
		void	map_rect(BRect *, BRect srcRect, BRect dstRect);

		BRect	fBounds;
		long	fCount;
		BPoint	*fPts;
};

inline BRect BPolygon::Frame() const
			{ return(fBounds); }

inline long BPolygon::CountPoints() const
			{ return(fCount); }

#endif
