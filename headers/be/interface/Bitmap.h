//******************************************************************************
//
//	File:		Bitmap.h
//
//	Description:	Client offscreen window class.
//
//	Copyright 1992-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_BITMAP_H
#define	_BITMAP_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef _WINDOW_H
#include "Window.h"
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BBitmap : public BObject {

public:
					BBitmap(BRect bounds,
							color_space depth,
							bool accepts_views = FALSE);
virtual				~BBitmap();

		void		SetBits(const void *data, long length, long offset, color_space);
		void		*Bits() const;
		long		BitsLength() const;
		long		BytesPerRow() const;
		color_space	ColorSpace() const;
		BRect		Bounds() const;

		// to mimic a BWindow:
virtual	void		AddChild(BView *view);
virtual	bool		RemoveChild(BView *view);
		long		CountChildren() const;
		BView		*ChildAt(long index) const;
		BView		*FindView(const char *view_name) const;
		BView		*FindView(BPoint point) const;
		bool		Lock();
		void		Unlock();
	
//------------------------------------------------------------------------------

private:
friend class BView;
friend void  _get_screen_bitmap_(BBitmap *,BRect,bool);

		char		*get_shared_pointer() const;
		void		set_bits(long offset, char *data, long length);
		void		set_bits_24(long offset, char *data, long length);
		void		set_bits_24_local_gray(long offset, char *data, long len);
		void		set_bits_24_local_256(long offset, uchar *data, long len);
		void		set_bits_24_24(long offset, char *data, long length);
		void		set_bits_8_24(long offset, char *data, long length);
		void		set_bits_gray_24(long offset, char *data, long length);
		long		get_server_token() const;
		
		void		*fBasePtr;
		long		fSize;
		color_space	fType;
		BRect		fBound;
		long		fRowBytes;
		BWindow		*fWindow;
		long		fServerToken;
		long		fToken;
};

inline long BBitmap::BytesPerRow() const
	{ return(fRowBytes); }

inline color_space BBitmap::ColorSpace() const
	{ return(fType); }

inline BRect BBitmap::Bounds() const
	{ return(fBound); }

inline void *BBitmap::Bits() const
	{ return((void *) get_shared_pointer()); }

inline long BBitmap::BitsLength() const
	{ return(fSize); }

#endif
