/******************************************************************************
//
//	File:		InterfaceDefs.h
//
//	Description:	Basic Interface Kit types.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1992-93, Be Incorporated
//
*******************************************************************************/

#ifndef	_INTERFACE_DEFS_H
#define	_INTERFACE_DEFS_H

#ifndef _BE_DEFS_H
#include <sys/BeDefs.h>
#endif
#ifndef _RECT_H
#include "Rect.h"
#endif

#ifdef __CPLUSPLUS__
extern "C" {
#endif

/*----------------------------------------------------------------*/

typedef struct
	{
		uchar		data[8];
	} pattern;

const pattern solid_front = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; 
const pattern mixed_colors = {0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55}; 
const pattern solid_back = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 

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
		rgb_color	last_color;
		long		last_entry;
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

enum { BACKSPACE = 0x08,
       RETURN = 0x0a,
       SPACE = 0x20,
       TAB = 0x09,
       ESCAPE = 0x1b,
       LEFT_ARROW = 0x1c,
       RIGHT_ARROW = 0x1d,
       UP_ARROW = 0x1e,
       DOWN_ARROW = 0x1f };

/*----------------------------------------------------------------*/

typedef enum {	HORIZONTAL,
		VERTICAL
	} orientation;

/*----------------------------------------------------------------*/

//??? This is temporary until alpha channel gets going
const uchar TRANSPARENT_8_BIT = 0xff;
const rgb_color TRANSPARENT_24_BIT = {0x77, 0x74, 0x73, 0x72};

#ifdef __CPLUSPLUS__
}
#endif

#endif
