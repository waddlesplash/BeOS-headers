/******************************************************************************
//
//	File:		InterfaceDefs.h
//
//	Description:	Basic Interface Kit types.  C++ only.
//
//	Copyright 1992-97, Be Incorporated
//
*******************************************************************************/

#pragma once

#ifndef	_INTERFACE_DEFS_H
#define	_INTERFACE_DEFS_H

#include <GraphicsDefs.h>
#include <OS.h>
#include <Rect.h>


struct key_info {
	uint32	modifiers;
	uint8	key_states[16];
};

/*----------------------------------------------------------------*/

#define B_UTF8_ELLIPSIS		"\xE2\x80\xA6"
#define B_UTF8_OPEN_QUOTE	"\xE2\x80\x9C"
#define B_UTF8_CLOSE_QUOTE	"\xE2\x80\x9D"
#define B_UTF8_COPYRIGHT	"\xC2\xA9"
#define B_UTF8_REGISTERED	"\xC2\xAE"
#define B_UTF8_TRADEMARK	"\xE2\x84\xA2"
#define B_UTF8_SMILING_FACE	"\xE2\x98\xBB"
#define B_UTF8_HIROSHI		"\xE5\xBC\x98"

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

struct key_map {
		uint32	version;
		uint32	caps_key;
		uint32	scroll_key;
		uint32	num_key;
		uint32	left_shift_key;
		uint32	right_shift_key;
		uint32	left_command_key;
		uint32	right_command_key;
		uint32	left_control_key;
		uint32	right_control_key;
		uint32	left_option_key;
		uint32	right_option_key;
		uint32	menu_key;
		uint32	lock_settings;
		int32	control_map[128];
		int32	option_caps_shift_map[128];
		int32	option_caps_map[128];
		int32	option_shift_map[128];
		int32	option_map[128];
		int32	caps_shift_map[128];
		int32	caps_map[128];
		int32	shift_map[128];
		int32	normal_map[128];
		int32	acute_dead_key[32];
		int32	grave_dead_key[32];
		int32	circumflex_dead_key[32];
		int32	dieresis_dead_key[32];
		int32	tilde_dead_key[32];
		uint32	acute_tables;
		uint32	grave_tables;
		uint32	circumflex_tables;
		uint32	dieresis_tables;
		uint32	tilde_tables;
};

struct mouse_map {
	uint32	left;
	uint32	right;
	uint32	middle;
};

/*----------------------------------------------------------------*/

enum border_style {
	B_PLAIN_BORDER,
	B_FANCY_BORDER,
	B_NO_BORDER
};

/*----------------------------------------------------------------*/

enum orientation {
	B_HORIZONTAL,
	B_VERTICAL
};

/*----------------------------------------------------------------*/

struct scroll_bar_info {
	bool	proportional;
	bool	double_arrows;
	int32	knob;
	int32	min_knob_size;
};

/*----------------------------------------------------------------*/

enum alignment {
	B_ALIGN_LEFT,
    B_ALIGN_RIGHT,
    B_ALIGN_CENTER
};

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


const color_map *system_colors();

status_t	set_screen_space(int32 index, uint32 res, bool stick = TRUE);

status_t	get_scroll_bar_info(scroll_bar_info *info);
status_t	set_scroll_bar_info(scroll_bar_info *info);

status_t	get_mouse_type(int32 *type);
status_t	set_mouse_type(int32 type);
status_t	get_mouse_map(mouse_map *map);
status_t	set_mouse_map(mouse_map *map);
status_t	get_click_speed(bigtime_t *speed);
status_t	set_click_speed(bigtime_t speed);
status_t	get_mouse_speed(int32 *speed);
status_t	set_mouse_speed(int32 speed);

status_t	get_key_repeat_rate(int32 *rate);
status_t	set_key_repeat_rate(int32 rate);
status_t	get_key_repeat_delay(bigtime_t *delay);
status_t	set_key_repeat_delay(bigtime_t  delay);

uint32		modifiers();
status_t	get_key_info(key_info *info);
void        get_key_map(key_map **map, char **key_buffer);
status_t	get_keyboard_id(uint16 *ID);
void		set_modifier_key(uint32 modifier, uint32 key);
void		set_keyboard_locks(uint32 modifiers);

rgb_color	keyboard_navigation_color();

int32		count_workspaces();
void		set_workspace_count(int32 count);
int32		current_workspace();
void		activate_workspace(int32 workspace);

bigtime_t	idle_time();

void		run_select_printer_panel();	
void		run_add_printer_panel();	

#endif













