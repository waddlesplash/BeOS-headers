//******************************************************************************
//
//	File:		Polygon.h
//
//	Description:	Client polygon class.
//
//	Written by:	Eric Knight
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
#include <sys/Object.h>
#endif

//------------------------------------------------------------------------------

class BPolygon : public BObject {

public:
			BPolygon(BPoint *ptArray, long numPoints);
			BPolygon();
			BPolygon(const BPolygon*);
virtual			~BPolygon();	
virtual	char		*ClassName();

	void		GetFrame(BRect* frame);
	void		AddPoints(BPoint *ptArray, long numPoints);
	long		CountPoints();
	void		MapToRect(BRect *srcRect, BRect *dstRect);
	void		PrintToStream();

//------------------------------------------------------------------------------
friend class BView;

private:
	void		compute_bounds();
	void		map_pt(BPoint *, BRect *srcRect, BRect *dstRect);
	void		map_rect(BRect *, BRect *srcRect, BRect *dstRect);

	BRect		fBounds;
	long		fCount;
	BPoint		*fPts;
};

inline char		*BPolygon::ClassName() { return "BPolygon"; };

inline void		BPolygon::GetFrame(BRect* frame)
			{ *frame = fBounds; };

inline long		BPolygon::CountPoints()
			{ return(fCount); };

#endif
