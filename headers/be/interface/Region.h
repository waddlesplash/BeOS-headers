//******************************************************************************
//
//	File:		Region.h
//
//	Description:	client region class.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1992-93, Be Incorporated
//
//******************************************************************************

#ifndef	_REGION_H
#define	_REGION_H

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

class BRegion : public BObject {

public:
			BRegion();
			BRegion(const BRegion*);
virtual			~BRegion();	

virtual	char		*ClassName();
		
	void		GetFrame(BRect* r);	
	void		SetToRect(const BRect *newBounds);
	bool		Intersects(const BRect *r);
	bool		Contains(BPoint pt);
	void		PrintToStream();
	void		OffsetBy(long dh, long dv);
	void		MakeEmpty();
	void		AddRect(const BRect *r);
	void		SubtractRect(const BRect *r);
	void		AddRegion(const BRegion*);
	void		SubtractRegion(const BRegion*);
	void		IntersectRegion(const BRegion*);

//------------------------------------------------------------------------------
friend class BView;
friend void copy_region_n(BRegion*, BRegion*, long);
friend void and_region_complex(BRegion*, BRegion*, BRegion*);
friend void and_region_1_to_n(BRegion*, BRegion*, BRegion*);
friend void and_region(BRegion*, BRegion*, BRegion*);
friend void append_region(BRegion*, BRegion*, BRegion*);
friend void r_or(long, long, BRegion*, BRegion*, BRegion*, long*, long *);
friend void or_region_complex(BRegion*, BRegion*, BRegion*);
friend void or_region_1_to_n(BRegion*, BRegion*, BRegion*);
friend void or_region_no_x(BRegion*, BRegion*, BRegion*);
friend void or_region(BRegion*, BRegion*, BRegion*);
friend void sub(long, long, BRegion*, BRegion*, BRegion*, long*, long*);
friend void sub_region_complex(BRegion*, BRegion*, BRegion*);
friend void r_sub(long , long, BRegion*, BRegion*, BRegion*, long*, long*);
friend void sub_region(BRegion*, BRegion*, BRegion*);

private:
	void		__AddRect(const BRect *r);
	void		set_size(long new_size);
	long		find_small_bottom(long y1, long y2, long *hint, long *where);

	long		f_count;
	long		f_data_size;
	BRect		f_bound;
	BRect		*f_data;
};

inline char		*BRegion::ClassName() { return "BRegion"; };

//------------------------------------------------------------------------------


#endif
