//******************************************************************************
//
//	File:		ColorControl.h
//
//	Description:	 a control for picking a color
//
//	Copyright 1996, Be Incorporated
//
//******************************************************************************

#ifndef _COLOR_CONTROL_H
#define _COLOR_CONTROL_H

#ifndef _CONTROL_H
#include <Control.h>
#endif
#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

/*------------------------------------------------------------*/

enum color_control_layout {
	B_CELLS_4x64 = 4,
	B_CELLS_8x32 = 8,
	B_CELLS_16x16 = 16,
	B_CELLS_32x8 = 32,
	B_CELLS_64x4 = 64
};

/*------------------------------------------------------------*/

class BColorControl : public BControl {
	DECLARE_CLASS_INFO(BControl);

public:
						BColorControl(	BPoint start,
										color_control_layout layout,
										long cell_size,
										const char *name,
										BMessage *message = NULL,
										bool use_offscreen = FALSE);
virtual					~BColorControl();

virtual	void			SetValue(long color_value);
virtual	void			SetValue(rgb_color color);
		rgb_color		ValueAsColor();

virtual	void			AttachedToWindow();
virtual	void			Draw(BRect updateRect);
virtual	void			MouseDown(BPoint where);
virtual	void			KeyDown(ulong key);

private:
		void			UpdateOffscreen();
		void			ColorRamp(	BRect r,
									BRect where,
									rgb_color c,
									short flag,
									bool focused);
		void			KbAdjustColor(ulong key);
		void			key_down32(ulong key);
		void			key_down8(ulong key);
static	BRect			CalcFrame(	BPoint start,
									color_control_layout layout,
									long size);

		long			fCellSize;
		long			fRows;
		long			fColumns;

		BBitmap			*fBitmap;
		BColorControl	*fOffscreenView;
		BColorControl	*fRealView;
		bool			fTracking;
		bool			fFocused;
		long			fFocusedComponent;
		bool			fRetainCache;
		long			fCachedIndex;
		bool			fast_set_value;
};

/*------------------------------------------------------------*/

#endif
