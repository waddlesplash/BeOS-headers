//******************************************************************************
//
//	File:		Bitmap.h
//
//	Description:	Client bitmap class.
//
//	Copyright 1992-93, Be Incorporated, All Rights Reserved.
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
#ifndef	_OBJECT_H
#include <support/Object.h>
#endif
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BBitmap : public BObject {
	DECLARE_CLASS_INFO(BObject);

public:
					BBitmap(BRect bounds, color_space);
virtual				~BBitmap();

		void		SetBits(void *data, long length, long offset, color_space);
		void		*Bits() const;
		long		BitsLength() const;
		long		BytesPerRow() const;
		color_space	ColorSpace() const;
		BRect		Bounds() const;

// ------------------------------------------------------------------

private:

friend class BView;
friend class BCursor;

		void		set_bits(long offset, char *data, long length);
		void		set_bits_24(long offset, char *data, long length);
		void		set_bits_24_tst(long offset, char *data, long length);
		void		set_bits_24_local_256(long offset, char *data, long len);
		void		set_bits_24_local_gray(long offset, char *data, long len);

		long		server_token;
		long		client_token;
		BRect		bound;
		color_space	type;
		long		rowbytes;
		long		bitmap_size;
		char		*shared_pointer;
};

inline long			BBitmap::BytesPerRow() const	{ return(rowbytes); }
inline long			BBitmap::BitsLength() const		{ return(bitmap_size); }
inline color_space	BBitmap::ColorSpace() const		{ return(type); }
inline BRect		BBitmap::Bounds() const			{ return(bound); }
inline void			*BBitmap::Bits() const			{ return(shared_pointer); }

#endif
