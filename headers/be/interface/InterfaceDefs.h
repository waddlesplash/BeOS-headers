/******************************************************************************
//
//	File:		InterfaceDefs.h
//
//	Description:	Basic Interface Kit types.
//
//	Copyright 1992-93, Be Incorporated
//
*******************************************************************************/

#ifndef	_INTERFACE_DEFS_H
#define	_INTERFACE_DEFS_H

#ifndef _SUPPORT_DEFS_H
#include <support/SupportDefs.h>
#endif
#ifndef _RECT_H
#include <interface/Rect.h>
#endif

#ifdef __CPLUSPLUS__
extern "C" {
#endif

/*----------------------------------------------------------------*/

typedef struct
	{
		uchar		data[8];
	} pattern;

/*----------------------------------------------------------------*/

extern const pattern solid_front;
extern const pattern mixed_colors;
extern const pattern solid_back;

/*----------------------------------------------------------------*/

typedef struct
	{
		uchar		red;
		uchar		green;
		uchar		blue;
		uchar		alpha;
	} rgb_color;

/*----------------------------------------------------------------*/

typedef	struct
	{
		long		id;
		rgb_color	color_list[256];
		uchar		inversion_map[256];
		uchar		index_map[32768];
	} color_map;

/*----------------------------------------------------------------*/

typedef enum { MONOCHROME_1_BIT = 1,
               GRAYSCALE_8_BIT = 2,
               COLOR_8_BIT = 4,
               RGB_24_BIT = 8 } color_space;
	      
/*----------------------------------------------------------------*/
typedef struct {
		color_space	mode;
		BRect		frame;
		void		*bits;
		long		bytes_per_row;
		long		reserved;
	} screen_info;

/*----------------------------------------------------------------*/

typedef enum {	OP_COPY,
		OP_OVER,
		OP_ERASE,
		OP_INVERT,
		OP_ADD,
		OP_SUBTRACT,
		OP_BLEND,
		OP_MIN,
		OP_MAX
	} drawing_mode;

/*----------------------------------------------------------------*/

enum {	BACKSPACE		= 0x08,
		RETURN			= 0x0a,
		ENTER			= 0x0a,
		SPACE			= 0x20,
		TAB				= 0x09,
		ESCAPE			= 0x1b,

		LEFT_ARROW		= 0x1c,
		RIGHT_ARROW		= 0x1d,
		UP_ARROW		= 0x1e,
		DOWN_ARROW		= 0x1f,

		INSERT			= 0x05,
		DELETE			= 0x7f,
		HOME			= 0x01,
		END				= 0x04,
		PAGE_UP			= 0x0b,
		PAGE_DOWN		= 0x0c,

		FUNCTION_KEY	= 0x10 };

enum {	F1_KEY			= 0x02,
		F2_KEY			= 0x03,
		F3_KEY			= 0x04,
		F4_KEY			= 0x05,
		F5_KEY			= 0x06,
		F6_KEY			= 0x07,
		F7_KEY			= 0x08,
		F8_KEY			= 0x09,
		F9_KEY			= 0x0a,
		F10_KEY			= 0x0b,
		F11_KEY			= 0x0c,
		F12_KEY			= 0x0d,
		PRINT_KEY		= 0x0e,
		SCROLL_KEY		= 0x0f,
		PAUSE_KEY		= 0x10 };

typedef	struct {
		ulong	control_map[128];
		ulong	caps_shift_map[128];
		ulong	shift_map[128];
		ulong	caps_map[128];
		ulong	normal_map[128];
	} key_map;

/*----------------------------------------------------------------*/

typedef enum {
	HORIZONTAL,
	VERTICAL
} orientation;

/*----------------------------------------------------------------*/

typedef enum {
	ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_CENTER
} alignment;

/*----------------------------------------------------------------*/

//??? This is temporary until alpha channel gets going
const uchar TRANSPARENT_8_BIT = 0xff;
const rgb_color TRANSPARENT_24_BIT = {0x77, 0x74, 0x73, 0x72};

#ifdef __CPLUSPLUS__
}
#endif

uchar		index_for_color(rgb_color c);
uchar		index_for_color(uchar r, uchar g, uchar b, uchar a = 0);
color_map	*system_colors();

long		count_screens();
void		get_screen_info(screen_info *info);
void		get_screen_info(long index, screen_info *info);

key_map		*system_key_map();
void		restore_key_map();
long		get_keyboard_id(ushort *ID);

#endif
