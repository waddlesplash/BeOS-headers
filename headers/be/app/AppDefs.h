/******************************************************************************

	File:			AppDefs.h

	Description:	Some common type definitions.

	Copyright 1993-94, Be Incorporated

******************************************************************************/

#ifndef _APP_DEFS_H
#define _APP_DEFS_H

#ifndef _SUPPORT_DEFS_H
#include <support/SupportDefs.h>
#endif

/* System Event codes */
enum {
	WINDOW_RESIZED = 'SYWR',
	WINDOW_MOVED = 'SYWM',
	WINDOW_CLOSED = 'SYWC', 
	CLOSE_REQUESTED = 'SYCR',
	QUIT_REQUESTED = 'SYQR',
	ACTIVATION = 'SYAC',
	MOUSE_DOWN = 'SYMD',
	MOUSE_UP = 'SYMU',
	MOUSE_MOVED = 'SYMM',
	MESSAGE_DROPPED = 'SYDR',
	PULSE = 'SYPS',
	KEY_DOWN = 'SYKD',
	VALUE_CHANGED = 'SYVC',
	VIEW_RESIZED = 'SYVR',
	VIEW_MOVED = 'SYVM',
	KEY_UP = 'SYKU',
	ACTIVATE_APP = 'SYAA'
};

/* other commands */
enum {
	NO_REPLY = 'NONE'
};

/* Data types */
enum {
	CHAR_TYPE = 'CHAR',
	SHORT_TYPE = 'SHRT',
	LONG_TYPE = 'LONG',
	UCHAR_TYPE = 'UCHR',
	USHORT_TYPE = 'USHT',
	BOOL_TYPE = 'BOOL',
	ULONG_TYPE = 'ULNG',
	FLOAT_TYPE = 'FLOT',
	DOUBLE_TYPE = 'DBLE',
	POINTER_TYPE = 'PNTR',
	OBJECT_TYPE = 'OPTR',
	POINT_TYPE = 'BPNT',
	RECT_TYPE = 'RECT',
	RGB_COLOR_TYPE = 'RGBC',
	PATTERN_TYPE = 'PATN',
	ASCII_TYPE = 'TEXT',
	RTF_TYPE = 'RTXF',
	STRING_TYPE = 'CSTR',
	MONOCHROME_1_BIT_TYPE = 'MNOB',
	GRAYSCALE_8_BIT_TYPE = 'GRYB',
	COLOR_8_BIT_TYPE = 'CLRB',
	RGB_24_BIT_TYPE = 'RGBB',
	TIFF_TYPE = 'TIFF',
	FILE_TYPE = 'FILE',
	TIME_TYPE = 'TIME',
	REF_TYPE = 'RREF',
	RAW_TYPE = 'RAWT',
	MONEY_TYPE = 'MULA',
	ANY_TYPE = 'ANYT'
};

#endif
