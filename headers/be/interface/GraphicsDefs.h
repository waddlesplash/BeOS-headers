/*******************************************************************************
/
/	File:			GraphicsDefs.h
/
/   Description:    Color space definitions.
/
/	Copyright 1992-98, Be Incorporated, All Rights Reserved
/
/******************************************************************************/


#ifndef _GRAPHICS_DEFS_H
#define _GRAPHICS_DEFS_H

#include <BeBuild.h>
#include <SupportDefs.h>

/*----------------------------------------------------------------*/

typedef struct pattern {
		uint8		data[8];
} pattern;

extern _IMPEXP_BE const pattern B_SOLID_HIGH;
extern _IMPEXP_BE const pattern B_MIXED_COLORS;
extern _IMPEXP_BE const pattern B_SOLID_LOW;

/*----------------------------------------------------------------*/

typedef struct rgb_color {
	uint8		red;
	uint8		green;
	uint8		blue;
	uint8		alpha;
} rgb_color;

extern _IMPEXP_BE const uint8 B_TRANSPARENT_8_BIT;
extern _IMPEXP_BE const rgb_color B_TRANSPARENT_32_BIT;

/*----------------------------------------------------------------*/

typedef struct color_map {
		int32		id;
		rgb_color	color_list[256];
		uint8		inversion_map[256];
		uint8		index_map[32768];
} color_map;

/*----------------------------------------------------------------*/

typedef enum
{
	B_NO_COLOR_SPACE =	0x0000,	/* byte in memory order, high bit first				*/
	
	/* linear color space (little endian is the default) */
	B_RGB32 = 			0x0008,	/* B[7:0]  G[7:0]  R[7:0]  -[7:0]					*/
	B_RGBA32 = 			0x2008,	/* B[7:0]  G[7:0]  R[7:0]  A[7:0]					*/
	B_RGB24 = 			0x0003,	/* B[7:0]  G[7:0]  R[7:0]							*/
	B_RGB16 = 			0x0005,	/* G[2:0],B[4:0]  R[4:0],G[5:3]						*/
	B_RGB15 = 			0x0010,	/* G[2:0],B[4:0]  	   -[0],R[4:0],G[4:3]			*/
	B_RGBA15 = 			0x2010,	/* G[2:0],B[4:0]  	   A[0],R[4:0],G[4:3]			*/
	B_CMAP8 = 			0x0004,	/* D[7:0]  											*/
	B_GRAY8 = 			0x0002,	/* Y[7:0]											*/
	B_GRAY1 = 			0x0001,	/* Y0[0],Y1[0],Y2[0],Y3[0],Y4[0],Y5[0],Y6[0],Y7[0]	*/

	/* big endian version, when the encoding is not endianess independant */
	B_RGB32_BIG =		0x1008,	/* -[7:0]  R[7:0]  G[7:0]  B[7:0]					*/
	B_RGBA32_BIG = 		0x3008,	/* A[7:0]  R[7:0]  G[7:0]  B[7:0]					*/
	B_RGB24_BIG = 		0x1003,	/* R[7:0]  G[7:0]  B[7:0]							*/
	B_RGB16_BIG = 		0x1005,	/* R[4:0],G[5:3]  G[2:0],B[4:0]						*/
	B_RGB15_BIG = 		0x1010,	/* -[0],R[4:0],G[4:3]  G[2:0],B[4:0]				*/
	B_RGBA15_BIG = 		0x3010,	/* A[0],R[4:0],G[4:3]  G[2:0],B[4:0]				*/

	/* little-endian declarations, for completness */
	B_RGB32_LITTLE = 	B_RGB32,
	B_RGBA32_LITTLE =	B_RGBA32,
	B_RGB24_LITTLE =	B_RGB24,
	B_RGB16_LITTLE =	B_RGB16,
	B_RGB15_LITTLE =	B_RGB15,
	B_RGBA15_LITTLE =	B_RGBA15,

	/* non linear color space */
	B_YUV422 = 			0x4000,	/* Y0[7:0]  Cb0[7:0]  Y1[7:0]  Cr0[7:0]  Y2[7:0]...	*/
								/* Cb2[7:0]  Y3[7:0]  Cr2[7:0]						*/
	B_YUV411 = 			0x4001,	/* Cb0[7:0]  Y0[7:0]  Cr0[7:0]  Y1[7:0]  Cb4[7:0]...*/
								/* Y2[7:0]  Cr4[7:0]  Y3[7:0]  Y4[7:0]  Y5[7:0]...	*/
								/* Y6[7:0]  Y7[7:0]	 								*/
	B_YUV420 = 			0x4002,	/* ????												*/
	B_YUV444 = 			0x4003,	/* ????												*/
	B_YUV9 = 			0x4004,	/* ????												*/
	B_YUV12 = 			0x4005,	/* ????												*/

	/* compatibility declarations */
	B_MONOCHROME_1_BIT = 	B_GRAY1,
	B_GRAYSCALE_8_BIT =		B_GRAY8,
	B_COLOR_8_BIT =			B_CMAP8,
	B_RGB_32_BIT =			B_RGB32,
	B_RGB_16_BIT =			B_RGB15,
	B_BIG_RGB_32_BIT =		B_RGB32_BIG,
	B_BIG_RGB_16_BIT =		B_RGB15_BIG
} color_space;

enum buffer_orientation {
	B_BUFFER_TOP_TO_BOTTOM,
	B_BUFFER_BOTTOM_TO_TOP
};

enum buffer_layout { 
	B_BUFFER_INTERLEAVED,
	B_BUFFER_NONINTERLEAVED,
	B_BUFFER_F1,
	B_BUFFER_F2
};
		      
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
	B_15_BIT_640x480   = 0x00040000,
	B_15_BIT_800x600   = 0x00080000,
	B_15_BIT_1024x768  = 0x00100000,
	B_15_BIT_1280x1024 = 0x00200000,
	B_15_BIT_1600x1200 = 0x00400000,
    B_15_BIT_1152x900  = 0x00800000,
	
	/* do not use B_FAKE_DEVICE--it will go away! */
	B_FAKE_DEVICE	   = 0x40000000,
	B_8_BIT_640x400	   = (int)0x80000000
};


#endif
