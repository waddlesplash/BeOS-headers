//******************************************************************************
//
//	File:		Bitmap.h
//
//	Description:	Client bitmap class.
//
//	Written by:	Benoit Schillings
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
#include <sys/Object.h>
#endif

//------------------------------------------------------------------------------

class BBitmap : public BObject {

public:
			BBitmap(BRect *bounds, color_space);
virtual			~BBitmap();
virtual	char		*ClassName();

	void		SetBits(void *data, long length, long offset,
				color_space);
	void		*Bits();
	long		BitsLength();
	long		BytesPerRow();
	color_space	ColorSpace();
	void		GetBounds(BRect *);

//------------------------------------------------------------------------------
friend class BView;

private:
		void		set_bits(long offset, char *data, long length);
		void		set_bits_24(long offset, char *data, long length);
		void		set_bits_24_tst(long offset, char *data, long length);
		void		set_bits_24_local_256(long offset, char *data, long length);
		void		set_bits_24_local_gray(long offset, char *data, long length);

	long		server_token;
	long		client_token;
	BRect		bound;
	color_space	type;
	long		rowbytes;
	long		bitmap_size;
	char		*shared_pointer;
};

inline long		BBitmap::BytesPerRow()	{ return(rowbytes); }
inline long		BBitmap::BitsLength()	{ return(bitmap_size); }
inline color_space	BBitmap::ColorSpace()	{ return(type); }
inline void		BBitmap::GetBounds(BRect *r)	{ *r = bound; }
inline void		*BBitmap::Bits()	{ return(shared_pointer); }
inline char		*BBitmap::ClassName() { return "BBitmap"; };

#endif
