//*****************************************************************************
//
//	File:		 GraphicsCard.h
//
//	Description: Application Server interface for graphics card add-ons
//
//	Copyright 1996, Be Incorporated
//
//******************************************************************************/

#ifndef _GRAPHICS_CARD_H
#define _GRAPHICS_CARD_H

#ifndef _INTERFACE_DEFS_H
#include <InterfaceDefs.h>
#endif

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
	B_SET_SCREEN_GAMMA
};

//----------------------------------------------------------------
// graphic add-on optional abilities

enum {
	B_CRT_CONTROL,
	B_GAMMA_CONTROL
};

//-------------------------------------------------------
// graphic add-on specific data structures

typedef struct {
	short           version;
	short           id;
	short			width;
	short			height;
	short			bits_per_pixel;
	short           flags;
	char            rgba_order[4];
	void            *bits;
	long            bytes_per_row;
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
	uchar           red[256];
	uchar           green[256];
	uchar           blue[256];
} screen_gamma;

typedef void (*graphics_card_hook) ();

/* debug calls */
extern "C" void    dprintf(const char *format, ...);
extern "C" bool    set_dprintf_enabled(bool);	/* returns old enable flag */

//-------------------------------------------------------
// count of the hook table

#define B_HOOK_COUNT  48

#endif








