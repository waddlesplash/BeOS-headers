//******************************************************************************
//
//	File:		ImageBuffer.h
//
//	Description:	Client offscreen window class.
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
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BImageBuffer : public BWindow {
	DECLARE_CLASS_INFO(BWindow);

public:
					BImageBuffer(BRect bounds, color_space);
virtual				~BImageBuffer();

		void		SetBits(void *data, long length, long offset, color_space);
		void		*Bits() const;
		long		BitsLength() const;
		long		BytesPerRow() const;
		color_space	ColorSpace() const;
		BRect		Bounds() const;
	
//------------------------------------------------------------------------------

private:
		char		*get_shared_pointer() const;
		void		set_bits(long offset, char *data, long length);
		void		set_bits_24(long offset, char *data, long length);
		void		set_bits_24_local_gray(long offset, char *data, long len);
		void		set_bits_24_local_256(long offset, char *data, long len);

		uchar		*base_pointer;
		long		bitmap_size;
		color_space	bitmap_type;
		BRect		bnd;
		long		rowbytes;
};

inline long BImageBuffer::BytesPerRow() const
	{ return(rowbytes); }

inline color_space BImageBuffer::ColorSpace() const
	{ return(bitmap_type); }

inline BRect BImageBuffer::Bounds() const
	{ return(bnd); }

inline void* BImageBuffer::Bits() const
	{ return(get_shared_pointer()); }

inline long BImageBuffer::BitsLength() const
	{ return(bitmap_size); }

#endif
