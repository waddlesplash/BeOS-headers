/******************************************************************************
//
//	File:		InterfaceDefs.h
//
//	Description:	Basic Interface Kit types.
//
//	Copyright 1992-96, Be Incorporated
//
*******************************************************************************/

#ifndef	_INTERFACE_DEFS_H
#define	_INTERFACE_DEFS_H

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif
#ifndef _OS_H
#include <OS.h>
#endif
#ifndef _RECT_H
#include <Rect.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------*/

typedef struct
	{
		uchar		data[8];
	} pattern;

/*----------------------------------------------------------------*/

extern const pattern B_SOLID_HIGH;
extern const pattern B_MIXED_COLORS;
extern const pattern B_SOLID_LOW;

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

typedef enum { B_MONOCHROME_1_BIT = 1,
               B_GRAYSCALE_8_BIT = 2,
               B_COLOR_8_BIT = 4,
               B_RGB_32_BIT = 8,
			   B_RGB_16_BIT = 16 } color_space;
	      
/*----------------------------------------------------------------*/
typedef struct {
		color_space	mode;
		BRect		frame;
		ulong		spaces;
		float		min_refresh_rate;
		float		max_refresh_rate;
		float		refresh_rate;
		uchar		h_position;
		uchar		v_position;
		uchar		h_size;
		uchar		v_size;
	} screen_info;

/*----------------------------------------------------------------*/

typedef enum {	B_OP_COPY,
		B_OP_OVER,
		B_OP_ERASE,
		B_OP_INVERT,
		B_OP_ADD,
		B_OP_SUBTRACT,
		B_OP_BLEND,
		B_OP_MIN,
		B_OP_MAX
	} drawing_mode;

/*----------------------------------------------------------------*/

enum {	B_BACKSPACE			= 0x08,
		B_RETURN			= 0x0a,
		B_ENTER				= 0x0a,
		B_SPACE				= 0x20,
		B_TAB				= 0x09,
		B_ESCAPE			= 0x1b,

		B_LEFT_ARROW		= 0x1c,
		B_RIGHT_ARROW		= 0x1d,
		B_UP_ARROW			= 0x1e,
		B_DOWN_ARROW		= 0x1f,

		B_INSERT			= 0x05,
		B_DELETE			= 0x7f,
		B_HOME				= 0x01,
		B_END				= 0x04,
		B_PAGE_UP			= 0x0b,
		B_PAGE_DOWN			= 0x0c,

		B_FUNCTION_KEY		= 0x10 };

enum {	B_F1_KEY			= 0x02,
		B_F2_KEY			= 0x03,
		B_F3_KEY			= 0x04,
		B_F4_KEY			= 0x05,
		B_F5_KEY			= 0x06,
		B_F6_KEY			= 0x07,
		B_F7_KEY			= 0x08,
		B_F8_KEY			= 0x09,
		B_F9_KEY			= 0x0a,
		B_F10_KEY			= 0x0b,
		B_F11_KEY			= 0x0c,
		B_F12_KEY			= 0x0d,
		B_PRINT_KEY			= 0x0e,
		B_SCROLL_KEY		= 0x0f,
		B_PAUSE_KEY			= 0x10 };

typedef	struct {
		ulong	version;
		ulong	caps_key;
		ulong	scroll_key;
		ulong	num_key;
		ulong	left_shift_key;
		ulong	right_shift_key;
		ulong	left_command_key;
		ulong	right_command_key;
		ulong	left_control_key;
		ulong	right_control_key;
		ulong	left_option_key;
		ulong	right_option_key;
		ulong	menu_key;
		ulong	lock_settings;
		ulong	control_map[128];
		ulong	option_caps_shift_map[128];
		ulong	option_caps_map[128];
		ulong	option_shift_map[128];
		ulong	option_map[128];
		ulong	caps_shift_map[128];
		ulong	caps_map[128];
		ulong	shift_map[128];
		ulong	normal_map[128];
		ulong	acute_dead_key[32];
		ulong	grave_dead_key[32];
		ulong	circumflex_dead_key[32];
		ulong	dieresis_dead_key[32];
		ulong	tilde_dead_key[32];
		ulong	acute_tables;
		ulong	grave_tables;
		ulong	circumflex_tables;
		ulong	dieresis_tables;
		ulong	tilde_tables;
	} key_map;

typedef struct {
	ulong	left;
	ulong	right;
	ulong	middle;
} mouse_map;

/*----------------------------------------------------------------*/

typedef enum {
	B_HORIZONTAL,
	B_VERTICAL
} orientation;

typedef struct {
	bool	proportional;
	bool	double_arrows;
	long	knob;
	long	min_knob_size;
} scroll_bar_info;

/*----------------------------------------------------------------*/

typedef enum {
	B_ALIGN_LEFT,
    B_ALIGN_RIGHT,
    B_ALIGN_CENTER
} alignment;

/*----------------------------------------------------------------*/

enum {
	B_CONTROL_TABLE				= 0x00000001,
	B_OPTION_CAPS_SHIFT_TABLE	= 0x00000002,
	B_OPTION_CAPS_TABLE			= 0x00000004,
	B_OPTION_SHIFT_TABLE		= 0x00000008,
	B_OPTION_TABLE				= 0x00000010,
	B_CAPS_SHIFT_TABLE			= 0x00000020,
	B_CAPS_TABLE				= 0x00000040,
	B_SHIFT_TABLE				= 0x00000080,
	B_NORMAL_TABLE				= 0x00000100
};

/*----------------------------------------------------------------*/

enum {
	B_SHIFT_KEY			= 0x00000001,
	B_COMMAND_KEY		= 0x00000002,
	B_CONTROL_KEY		= 0x00000004,
	B_CAPS_LOCK			= 0x00000008,
	B_SCROLL_LOCK		= 0x00000010,
	B_NUM_LOCK			= 0x00000020,
	B_OPTION_KEY		= 0x00000040,
	B_MENU_KEY			= 0x00000080,
	B_LEFT_SHIFT_KEY	= 0x00000100,
	B_RIGHT_SHIFT_KEY	= 0x00000200,
	B_LEFT_COMMAND_KEY	= 0x00000400,
	B_RIGHT_COMMAND_KEY	= 0x00000800,
	B_LEFT_CONTROL_KEY	= 0x00001000,
	B_RIGHT_CONTROL_KEY	= 0x00002000,
	B_LEFT_OPTION_KEY	= 0x00004000,
	B_RIGHT_OPTION_KEY	= 0x00008000
};

/*----------------------------------------------------------------*/

#define B_FONT_NAME_LENGTH 64
typedef char font_name[B_FONT_NAME_LENGTH + 1];
typedef font_name symbol_set_name;

/*----------------------------------------------------------------*/

//??? This is temporary until alpha channel gets going
extern const uchar B_TRANSPARENT_8_BIT;
extern const rgb_color B_TRANSPARENT_32_BIT;

#ifdef __cplusplus
}
#endif

uchar		index_for_color(rgb_color c);
uchar		index_for_color(uchar r, uchar g, uchar b, uchar a = 0);
rgb_color	desktop_color();
void		set_desktop_color(rgb_color c, bool stick = TRUE);
color_map	*system_colors();


/*----------------------------------------------------------------*/

long		count_screens();
void		get_screen_info(screen_info *info);
void		get_screen_info(long index, screen_info *info);

enum {
	B_8_BIT_640x480    = 0x00000001,
	B_8_BIT_800x600    = 0x00000002,
	B_8_BIT_1024x768   = 0x00000004,
	B_8_BIT_1280x1024  = 0x00000008,
	B_8_BIT_1600x1200  = 0x00000010,
	B_16_BIT_640x480   = 0x00000020,
	B_16_BIT_800x600   = 0x00000040,
	B_16_BIT_1024x768  = 0x00000080,
	B_16_BIT_1280x1024 = 0x00000100,
	B_16_BIT_1600x1200 = 0x00000200,
	B_32_BIT_640x480   = 0x00000400,
	B_32_BIT_800x600   = 0x00000800,
	B_32_BIT_1024x768  = 0x00001000,
	B_32_BIT_1280x1024 = 0x00002000,
	B_32_BIT_1600x1200 = 0x00004000,
    B_8_BIT_1152x900   = 0x00008000,
    B_16_BIT_1152x900  = 0x00010000,
    B_32_BIT_1152x900  = 0x00020000,
	B_8_BIT_640x400	   = 0x80000000
};

long		set_screen_space(long index, ulong res, bool stick = TRUE);
long		set_screen_refresh_rate(long index, float rate, bool stick = TRUE);
long		adjust_crt(long index, uchar x_position, uchar y_position,
					   uchar x_size, uchar y_size, bool stick = TRUE);

long		get_dock_width(float *width);

ulong		modifiers();
key_map		*system_key_map();
void		restore_key_map();
long		get_keyboard_id(ushort *ID);
void		set_modifier_key(ulong modifier, ulong key);
void		set_keyboard_locks(ulong modifiers);

long		get_scroll_bar_info(scroll_bar_info *info);
long		set_scroll_bar_info(scroll_bar_info *info);

long		get_mouse_type(long *type);
long		set_mouse_type(long type);
long		get_mouse_map(mouse_map *map);
long		set_mouse_map(mouse_map *map);
long		get_click_speed(double *speed);
long		set_click_speed(double speed);
long		get_mouse_speed(long *speed);
long		set_mouse_speed(long speed);

long		get_key_repeat_rate(int     *rate);
long		set_key_repeat_rate(int      rate);
long		get_key_repeat_delay(double *delay);
long		set_key_repeat_delay(double  delay);


long		count_fonts();
void		get_font_name(long index, font_name* name);
long		count_symbol_sets();
void		get_symbol_set_name(long index, symbol_set_name* name);

void		activate_app(team_id);

void		animate_window(	BRect from,
							BRect to,
							long num_frames,
							bool restore_last);

long		count_workspaces();
void		set_workspace_count(long count);
long		current_workspace();
void		activate_workspace(long workspace);

double		idle_time();

#endif
