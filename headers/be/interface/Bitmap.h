//******************************************************************************
//
//	File:		Bitmap.h
//
//	Description:	Client offscreen window class.
//
//	Copyright 1992-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#pragma once

#ifndef	_BITMAP_H
#define	_BITMAP_H

#include <InterfaceDefs.h>
#include <Window.h>

//------------------------------------------------------------------------------

class BBitmap : public BArchivable {

public:
					BBitmap(BRect bounds,
							color_space depth,
							bool accepts_views = FALSE,
							bool need_contiguous = FALSE);
					BBitmap(BMessage *data);
virtual				~BBitmap();
static	BBitmap		*Instantiate(BMessage *data);
virtual	status_t	Archive(BMessage *data, bool deep = true) const;
		bool		IsValid() const;

		void		SetBits(const void *data,
							int32 length,
							int32 offset,
							color_space cs);
		void		*Bits() const;
		int32		BitsLength() const;
		int32		BytesPerRow() const;
		color_space	ColorSpace() const;
		BRect		Bounds() const;

		// to mimic a BWindow:
virtual	void		AddChild(BView *view);
virtual	bool		RemoveChild(BView *view);
		int32		CountChildren() const;
		BView		*ChildAt(int32 index) const;
		BView		*FindView(const char *view_name) const;
		BView		*FindView(BPoint point) const;
		bool		Lock();
		void		Unlock();
	
virtual status_t	Perform(uint32 d, void *arg);

//-----------------------------------------------------------------------

private:
friend class BView;
friend void  _get_screen_bitmap_(BBitmap *,BRect,bool);

virtual	void		_ReservedBitmap1();
virtual	void		_ReservedBitmap2();
virtual	void		_ReservedBitmap3();

					BBitmap(const BBitmap &);
		BBitmap		&operator=(const BBitmap &);

		char		*get_shared_pointer() const;
		void		set_bits(long offset, char *data, long length);
		void		set_bits_24(long offset, char *data, long length);
		void		set_bits_24_local_gray(long offset, char *data, long len);
		void		set_bits_24_local_256(long offset, uchar *data, long len);
		void		set_bits_24_24(long offset, char *data, long length, bool big_endian_dst);
		void		set_bits_8_24(long offset, char *data, long length, bool big_endian_dst);
		void		set_bits_gray_24(long offset, char *data, long length, bool big_endian_dst);
		int32		get_server_token() const;
		void		InitObject(BRect bounds, color_space depth, bool accept,
															    bool contiguous);
		
		void		*fBasePtr;
		int32		fSize;
		color_space	fType;
		BRect		fBound;
		int32		fRowBytes;
		BWindow		*fWindow;
		int32		fServerToken;
		int32		fToken;
		bool		fContiguous;
		area_id		fArea;
		uint32		_reserved[3];
};

#endif
