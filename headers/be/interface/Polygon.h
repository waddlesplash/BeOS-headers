//******************************************************************************
//
//	File:		Polygon.h
//
//	Description:	Client polygon class.
//
//	Copyright 1992-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#pragma once

#ifndef	_POLYGON_H
#define	_POLYGON_H

#include <InterfaceDefs.h>
#include <Rect.h>

//------------------------------------------------------------------------------

class BPolygon {

public:
					BPolygon(const BPoint *ptArray, int32 numPoints);
					BPolygon();
					BPolygon(const BPolygon *poly);
virtual				~BPolygon();	

		BPolygon	&operator=(const BPolygon &from);

		BRect		Frame() const;
		void		AddPoints(const BPoint *ptArray, int32 numPoints);
		int32		CountPoints() const;
		void		MapTo(BRect srcRect, BRect dstRect);
		void		PrintToStream() const;

//------------------------------------------------------------------------------

private:

friend class BView;

		void	compute_bounds();
		void	map_pt(BPoint *, BRect srcRect, BRect dstRect);
		void	map_rect(BRect *, BRect srcRect, BRect dstRect);

		BRect	fBounds;
		int32	fCount;
		BPoint	*fPts;
};

#endif
