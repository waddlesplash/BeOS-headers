//******************************************************************************
//
//	File:		WindowScreen.h
//
//	Description:	Client window class for direct screen access.
//
//	Copyright 1996, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_WINDOW_SCREEN_H
#define	_WINDOW_SCREEN_H

#ifndef _WINDOW_H
#include <Window.h>
#endif
#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif
#ifndef _OS_H
#include <OS.h>
#endif
#ifndef _IMAGE_H
#include <image.h>
#endif
#ifndef _GRAPHICS_CARD_H
#include <GraphicsCard.h>
#endif

// private struct
typedef struct {
    area_id               memory_area;
    area_id               io_area;
	long                  record;
	int                   vol_id;
} _direct_screen_info_;

typedef long (*_add_on_control_)(ulong,void *);

class BWindowScreen : public BWindow {

public:
                    BWindowScreen(const char *title, ulong space);
virtual             ~BWindowScreen();
virtual void        Quit(void);
		long        Error();
virtual void        ScreenConnected(bool active);
        void        Disconnect();
virtual	void		WindowActivated(bool active);
virtual void		WorkspaceActivated(long ws, bool state);
virtual void		ScreenChanged(BRect screen_size, color_space depth);
        void        SetColorList(rgb_color *list, long first_index = 0, long last_index = 255);
		long        SetSpace(ulong space);
		bool        CanControlFrameBuffer();
		long        ProposeFrameBuffer(short bits_per_pixel,
		                               short width,
									   short *height,
									   short *bytes_per_row = NULL);
		long        SetFrameBuffer(short height);
		long        SetFrameBuffer(short height,
		                           short display_width, short display_height,
								   short display_x = 0, short display_y = 0);
		long        SetDisplayArea(short width, short height,
		                           short display_x = 0, short display_y = 0);
		long        MoveDisplayArea(short x, short y);
 inline void        *IOBase();
 inline rgb_color   *ColorList();
 inline frame_buffer_info  *FrameBufferInfo();
 inline graphics_card_hook CardHookAt(long index);
 inline graphics_card_info *CardInfo();
		
private:
        bool                  direct_enable;
		bool                  work_state;
		bool                  window_state;
		char                  addon_state;
		char                  space_mode;
        long                  lock_state;
		long                  screen_index;
		long                  memory_area, io_area;
		long                  error_code;
		void                  *io_buffer;
		ulong                 old_space;
		ulong                 new_space;
		ulong                 space0;
		image_id              addon_image;
		rgb_color             colorList[256];
		_add_on_control_      addon_ctrl_jmp;
        graphics_card_info    card_info;
		graphics_card_hook    hooks[B_HOOK_COUNT]; 
		_direct_screen_info_  info;
		frame_buffer_info     format_info;
		
static	BRect		CalcFrame(long index, long space, ulong *old_space);
        void        SetActiveState(long state);
        long        SetLockState(long state);
		long        SyncAddons();
		void        GetCardInfo();
};

frame_buffer_info *BWindowScreen::FrameBufferInfo() {
    return &format_info;    
}

graphics_card_info *BWindowScreen::CardInfo() {
    return &card_info;    
}

graphics_card_hook BWindowScreen::CardHookAt(long index) {
    return hooks[index];    
}

rgb_color *BWindowScreen::ColorList() {
    return colorList;
}

void *BWindowScreen::IOBase() {
    return io_buffer;
}

#endif











