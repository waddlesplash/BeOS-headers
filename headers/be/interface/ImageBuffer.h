//******************************************************************************
//
//	File:		ImageBuffer.h
//
//	Description:	Client offscreen window class.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1992-93, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_IMAGE_BUFFER_H
#define	_IMAGE_BUFFER_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef _WINDOW_H
#include "Window.h"
#endif

//------------------------------------------------------------------------------

class BImageBuffer : public BWindow {

public:
			BImageBuffer(BRect *bounds, color_space);
virtual			~BImageBuffer();
virtual	char		*ClassName();

	void		SetBits(void *data, long length, long offset,
				color_space);
	void		*Bits();
	long		BitsLength();
	long		BytesPerRow();
	color_space	ColorSpace();
	void		GetBounds(BRect *);
	
//------------------------------------------------------------------------------

private:
	char		*get_shared_pointer();
	void		set_bits(long offset, char *data, long length);
	void		set_bits_24(long offset, char *data, long length);
	void		set_bits_24_local_gray(long offset, char *data, long length);
	void		set_bits_24_local_256(long offset, char *data, long length);

	uchar		*base_pointer;
	long		bitmap_size;
	color_space	bitmap_type;
	BRect		bnd;
	long		rowbytes;
};

inline long		BImageBuffer::BytesPerRow()	{ return(rowbytes); }
inline color_space	BImageBuffer::ColorSpace()	{ return(bitmap_type); }
inline void		BImageBuffer::GetBounds(BRect *r)	{ *r = bnd; }
inline void*		BImageBuffer::Bits()	{ return(get_shared_pointer()); }
inline long		BImageBuffer::BitsLength()	{ return(bitmap_size); }
inline char		*BImageBuffer::ClassName() { return "BImageBuffer"; };

#endif
