/*******************************************************************************
/
/	File:			Screen.h
/
/   Description:    BScreen provides information about a screen's current
/                   display settings.  It also lets you set the Desktop color.
/
/	Copyright 1993-98, Be Incorporated, All Rights Reserved
/
/******************************************************************************/

#ifndef _SCREEN_H
#define _SCREEN_H

#include <BeBuild.h>
#include <GraphicsDefs.h>
#include <Rect.h>

/*----------------------------------------------------------------*/
/*----- BScreen structures and declarations ----------------------*/

struct screen_id { int32 id; };

extern _IMPEXP_BE const screen_id B_MAIN_SCREEN_ID;

class BWindow;
class BPrivateScreen;

/*----------------------------------------------------------------*/
/*----- BScreen class --------------------------------------------*/

class BScreen {
public:  
        BScreen( screen_id id=B_MAIN_SCREEN_ID );
        BScreen( BWindow *win );
        ~BScreen();

        bool   			IsValid();
        status_t		SetToNext();
  
        color_space		ColorSpace();
        BRect			Frame();
        screen_id		ID();

        void*			BaseAddress();
        uint32			BytesPerRow();
        status_t		WaitForRetrace();
  
        uint8			IndexForColor( rgb_color rgb );
        uint8			IndexForColor( uint8 r, uint8 g, uint8 b, uint8 a=255 );
        rgb_color		ColorForIndex( const uint8 index );
        uint8			InvertIndex( uint8 index );
  
const   color_map*		ColorMap();

        rgb_color		DesktopColor();
        void			SetDesktopColor( rgb_color rgb, bool stick=true );

        BPrivateScreen*	private_screen();

/*----- Private or reserved -----------------------------------------*/
private:
		BScreen			&operator=(const BScreen &screen);
						BScreen(const BScreen &screen);

        BPrivateScreen 	*screen;
};


/*----------------------------------------------------------------*/
/*----- inline definitions ---------------------------------------*/

inline uint8 BScreen::IndexForColor( rgb_color rgb )
  { return IndexForColor(rgb.red,rgb.green,rgb.blue,rgb.alpha); }

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/

#endif /* _SCREEN_H */
