//******************************************************************************
//
//	File:		Screen.h
//
//	Description:	BScreen class header.
//	
//	Copyright 1993-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************


#ifndef _SCREEN_H
#define _SCREEN_H

#include <GraphicsDefs.h>
#include <Rect.h>

typedef struct { int32 id; } screen_id;

extern const screen_id B_MAIN_SCREEN_ID;


class BWindow;
class BPrivateScreen;


class BScreen {
public:  
        BScreen( screen_id id=B_MAIN_SCREEN_ID );
        BScreen( BWindow *win );
        ~BScreen();

        bool   			IsValid();
  
        color_space		ColorSpace();
        BRect			Frame();
        screen_id		ID();

        void*			BaseAddress();
        uint32			BytesPerRow();
        status_t		WaitForRetrace();
  
        uint8			IndexForColor( rgb_color rgb );
        uint8			IndexForColor( uint8 r, uint8 g, uint8 b, uint8 a=0 );
        rgb_color		ColorForIndex( const uint8 index );
        uint8			InvertIndex( uint8 index );
  
const   color_map*		ColorMap();

        rgb_color		DesktopColor();
        void			SetDesktopColor( rgb_color rgb, bool stick=true );

        BPrivateScreen*	private_screen();

private:
        status_t		SetToNext();
        BPrivateScreen 	*screen;
};


inline uint8 BScreen::IndexForColor( rgb_color rgb )
  { return IndexForColor(rgb.red,rgb.green,rgb.blue,rgb.alpha); }


#endif
