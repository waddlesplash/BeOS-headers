/******************************************************************************
//
//	File:		GraphicsDefs.h
//
//	Description:	Graphics and Display types, usable by C or C++
//
//	Copyright 1992-97, Be Incorporated
//
******************************************************************************/


#ifndef _GRAPHICS_DEFS_H
#define _GRAPHICS_DEFS_H

#include <SupportDefs.h>

/*----------------------------------------------------------------*/

typedef struct pattern {
		uint8		data[8];
} pattern;

extern const pattern B_SOLID_HIGH;
extern const pattern B_MIXED_COLORS;
extern const pattern B_SOLID_LOW;

/*----------------------------------------------------------------*/

typedef struct rgb_color {
	uint8		red;
	uint8		green;
	uint8		blue;
	uint8		alpha;
} rgb_color;

extern const uint8 B_TRANSPARENT_8_BIT;
extern const rgb_color B_TRANSPARENT_32_BIT;

/*----------------------------------------------------------------*/

typedef struct color_map {
		int32		id;
		rgb_color	color_list[256];
		uint8		inversion_map[256];
		uint8		index_map[32768];
} color_map;

/*----------------------------------------------------------------*/

typedef enum {
     	B_NO_COLOR_SPACE = 0,
	    B_MONOCHROME_1_BIT = 1,
		B_GRAYSCALE_8_BIT = 2,
		B_COLOR_8_BIT = 4,
		
		/* multi-byte direct pixels (RGB bits, bytes separated by spaces) */
		B_RGB_32_BIT = 8,		/* Little-endian (8B 8G 8R 8A) */
		B_RGB_16_BIT = 16,		/* Little-endian (3G5B 1A5R2G) */
		B_BIG_RGB_32_BIT = 32,	/* Big-endian    (8A 8R 8G 8B) */
		B_BIG_RGB_16_BIT = 64	/* Big-endian    (1A5R2G 3G5B) */
} color_space;
	      
/*----------------------------------------------------------------*/

enum drawing_mode {
	B_OP_COPY,
	B_OP_OVER,
	B_OP_ERASE,
	B_OP_INVERT,
	B_OP_ADD,
	B_OP_SUBTRACT,
	B_OP_BLEND,
	B_OP_MIN,
	B_OP_MAX,
	B_OP_SELECT
};



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
	
	/* do not use B_FAKE_DEVICE--it will go away! */
	B_FAKE_DEVICE	   = 0x40000000,
	B_8_BIT_640x400	   = (int)0x80000000
};




#endif







