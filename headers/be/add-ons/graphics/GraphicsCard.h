//*****************************************************************************
//
//	File:		 GraphicsCard.h
//
//	Description: Application Server interface for graphics card add-ons
//
//	Copyright 1996-97, Be Incorporated
//
//******************************************************************************/

#pragma once

#ifndef _GRAPHICS_CARD_H
#define _GRAPHICS_CARD_H

#include <GraphicsDefs.h>

//----------------------------------------------------------------
// graphic add-on commands

enum {
	B_OPEN_GRAPHICS_CARD,
	B_CLOSE_GRAPHICS_CARD,
	B_GET_GRAPHICS_CARD_INFO,
	B_GET_GRAPHICS_CARD_HOOKS,
	B_SET_INDEXED_COLOR,
	B_GET_SCREEN_SPACES,
	B_CONFIG_GRAPHICS_CARD,
	B_GET_REFRESH_RATES,
	B_SET_SCREEN_GAMMA,
	
	B_GET_INFO_FOR_CLONE_SIZE,
	B_GET_INFO_FOR_CLONE,
	B_SET_CLONED_GRAPHICS_CARD,
	B_CLOSE_CLONED_GRAPHICS_CARD,	
	B_PROPOSE_FRAME_BUFFER,
	B_SET_FRAME_BUFFER,
	B_SET_DISPLAY_AREA,
	B_MOVE_DISPLAY_AREA}
;

//----------------------------------------------------------------
// graphic add-on optional abilities

enum {
	B_CRT_CONTROL = 0x0001,
	B_GAMMA_CONTROL = 0x0002,
	B_FRAME_BUFFER_CONTROL = 0x0004
};

//-------------------------------------------------------
// graphic add-on specific data structures

typedef struct {
	short           version;
	short           id;
	void            *frame_buffer;
	char            rgba_order[4];
	short           flags;
	short			bits_per_pixel;
	short           bytes_per_row;
	short			width;
	short			height;
} graphics_card_info;


typedef struct {
	long	        index;
	rgb_color       color;
} indexed_color;


typedef struct {
	ulong           space;
	float           refresh_rate;
	uchar           h_position;
	uchar           v_position;
	uchar           h_size;
	uchar           v_size;
} graphics_card_config;


typedef struct {
	float           min;
	float           max;
	float           current;
} refresh_rate_info;


typedef struct {
	void            *screen_base;
	void            *io_base;
	ulong           vendor_id;
	ulong           device_id;
	ulong           _reserved1_;
	ulong           _reserved2_;
} graphics_card_spec;


typedef struct {
	short           x1;
	short           y1;
	short           x2;
	short           y2;
	rgb_color       color;
} rgb_color_line;


typedef struct {
	short           x1;
	short           y1;
	short           x2;
	short           y2;
	uchar           color;
} indexed_color_line;


typedef struct {
    short           bits_per_pixel;
	short           bytes_per_row;
	short           width;
	short           height;
    short           display_width;
	short           display_height;
	short           display_x;
	short           display_y;
} frame_buffer_info;


typedef struct {
	uchar           red[256];
	uchar           green[256];
	uchar           blue[256];
} screen_gamma;

typedef void (*graphics_card_hook) ();

#ifdef __cplusplus
extern "C" {
#endif

/* debug calls for version 1 */
void    dprintf(const char *format, ...);
bool    set_dprintf_enabled(bool);	/* returns old enable flag */

#ifdef __cplusplus
}
#endif

//-------------------------------------------------------
// count of the hook table

#define B_HOOK_COUNT  48

#endif








