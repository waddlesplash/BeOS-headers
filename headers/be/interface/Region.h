/*******************************************************************************
/
/	File:			Region.h
/
/   Description:    BRegion represents an area that's composed of individual
/                   rectangles.
/
/	Copyright 1992-98, Be Incorporated, All Rights Reserved
/
*******************************************************************************/

#ifndef	_REGION_H
#define	_REGION_H

#include <BeBuild.h>
#include <Rect.h>

/* Integer rect used to define a cliping rectangle. All bounds are included */
/* Moved from DirectWindow.h */
typedef struct {
	int32		left;
	int32		top;
	int32		right;
	int32		bottom;
} clipping_rect;

namespace BPrivate {
	class TestView;
}

class BDataIO;

/*----------------------------------------------------------------*/
/*----- BRegion class --------------------------------------------*/

class BRegion {

public:
				BRegion();
				BRegion(const BRegion &region);
				BRegion(const BRect rect);
virtual			~BRegion();	

		BRegion	&operator=(const BRegion &from);

		BRect	Frame() const;
clipping_rect	FrameInt() const;
		BRect	RectAt(int32 index) const;
clipping_rect	RectAtInt(int32 index) const;
		int32	CountRects() const;
		void	Set(BRect newBounds);
		void	Set(clipping_rect newBounds);
		bool	Intersects(BRect r) const;
		bool	Intersects(clipping_rect r) const;
		bool	Contains(BPoint pt) const;
		bool	Contains(int32 x, int32 y);
		void	PrintToStream() const;
		void	OffsetBy(int32 dh, int32 dv);
		void	MakeEmpty();
		void	Include(BRect r);
		void	Include(clipping_rect r);
		void	Include(const BRegion*);
		void	Exclude(BRect r);
		void	Exclude(clipping_rect r);
		void	Exclude(const BRegion*);
		void	IntersectWith(const BRegion*);

/*----- Private or reserved -----------------------------------------*/

private:

struct region;
friend	class	DecorImagePart;
friend	class	BPrivate::TestView;
friend	void	region2BRegion(region *r, BRegion *b);

friend	class	BView;
friend	class	BDirectWindow;
friend	void	clear_region(BRegion *a_region);
friend	void	copy_region(BRegion *src_region, BRegion *dst_region);
friend	void	copy_region_n(BRegion*, BRegion*, long);
friend	void	and_region(BRegion*, BRegion*, BRegion*);
friend	void	or_region(BRegion*, BRegion*, BRegion*);
friend	void	sub_region(BRegion*, BRegion*, BRegion*);
friend	void	set_region(BRegion *, clipping_rect *);
friend	int32	find_span_between(const BRegion *, int32, int32);
friend	void	set_size(BRegion *, int32);
friend	void	compress_spans(BRegion *spans);

		void	_AddRect(clipping_rect r);
		void	set_size(long new_size);
		long	find_small_bottom(long y1, long y2, long *hint, long *where);

private:
		long	count;
		long	data_size;
		clipping_rect	bound;
		clipping_rect	*data;
};

BDataIO& operator<<(BDataIO& io, const BRegion& region);

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/

#endif /* _REGION_H */
