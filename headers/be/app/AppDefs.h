/******************************************************************************

	File:			AppDefs.h

	Description:	Some common type definitions.

	Copyright 1993-96, Be Incorporated

******************************************************************************/

#ifndef _APP_DEFS_H
#define _APP_DEFS_H

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

/* System Message codes */
enum {
	B_ABOUT_REQUESTED		= '_ABR',
	B_ACTIVATE 				= '_ATV',
	B_WINDOW_ACTIVATED		= '_ACT',
	B_APP_ACTIVATED			= '_ACT',	/* ## SAME AS B_WINDOW_ACTIVATED ## */
	B_ARGV_RECEIVED 		= '_ARG',
	B_QUIT_REQUESTED 		= '_QRQ',
	B_CLOSE_REQUESTED 		= '_QRQ',	/* ## SAME AS B_QUIT_REQUESTED ## */
	B_KEY_DOWN 				= '_KYD',
	B_KEY_UP 				= '_KYU',
	B_MESSAGE_DROPPED 		= '_MDP',
	B_MINIMIZE				= '_WMN',
	B_MOUSE_DOWN 			= '_MDN',
	B_MOUSE_MOVED 			= '_MMV',
	B_MOUSE_UP 				= '_MUP',
	B_PANEL_CLOSED			= '_PCL',
	B_PULSE 				= '_PUL',
	B_READY_TO_RUN 			= '_RTR',
	B_REFS_RECEIVED 		= '_RRC',
	B_SAVE_REQUESTED 		= '_SRQ',
	B_SCREEN_CHANGED 		= '_SCH',
	B_VALUE_CHANGED 		= '_VCH',
	B_VIEW_MOVED 			= '_VMV',
	B_VIEW_RESIZED 			= '_VRS',
	B_WINDOW_MOVED 			= '_WMV',
	B_WINDOW_RESIZED 		= '_WRS',
	B_WORKSPACES_CHANGED	= '_WCG',
	B_WORKSPACE_ACTIVATED	= '_WAC',
	B_ZOOM					= '_WZM',
	B_HANDLERS_REQUESTED	= '_RCR',
	_APP_MENU_				= '_AMN',
	_HEAP_WATCH_			= '_HPW',
	_MENU_EVENT_ 			= '_MEV',
	_SAVE_PACKAGE_			= '_SVP',
	_PULSE_ENABLED_			= '_PBL',
	_QUIT_ 					= '_QIT',
	_VOLUME_MOUNTED_ 		= '_NVL',
	_VOLUME_UNMOUNTED_		= '_VRM',
	_OPEN_IN_WORKSPACE_		= '_OWS'
};

/* other commands */
enum {
	B_CUT 						= 'CCUT',
	B_COPY 						= 'COPY',
	B_PASTE 					= 'PSTE',
	B_HANDLERS_INFO				= 'RINF',
	B_MESSAGE_NOT_UNDERSTOOD	= 'MNOT',
	B_NO_REPLY 					= 'NONE'
};

/* Data types */
enum {
	B_ANY_TYPE 					= 'ANYT',
	B_ASCII_TYPE 				= 'TEXT',
	B_BOOL_TYPE 				= 'BOOL',
	B_CHAR_TYPE 				= 'CHAR',
	B_COLOR_8_BIT_TYPE 			= 'CLRB',
	B_DOUBLE_TYPE 				= 'DBLE',
	B_FLOAT_TYPE 				= 'FLOT',
	B_GRAYSCALE_8_BIT_TYPE		= 'GRYB',
	B_LONG_TYPE 				= 'LONG',
	B_MESSENGER_TYPE			= 'MSNG',
	B_MONEY_TYPE 				= 'MULA',
	B_MONOCHROME_1_BIT_TYPE 	= 'MNOB',
	B_OBJECT_TYPE 				= 'OPTR',
	B_PATTERN_TYPE 				= 'PATN',
	B_POINTER_TYPE 				= 'PNTR',
	B_POINT_TYPE 				= 'BPNT',
	B_RAW_TYPE 					= 'RAWT',
	B_RECORD_TYPE 				= 'RCID',
	B_RECT_TYPE 				= 'RECT',
	B_REF_TYPE 					= 'RREF',
	B_RGB_24_BIT_TYPE 			= 'RGBB',
	B_RGB_COLOR_TYPE 			= 'RGBC',
	B_RTF_TYPE 					= 'RTXF',
	B_SHORT_TYPE 				= 'SHRT',
	B_STRING_TYPE 				= 'CSTR',
	B_TIFF_TYPE 				= 'TIFF',
	B_TIME_TYPE 				= 'TIME',
	B_UCHAR_TYPE 				= 'UCHR',
	B_ULONG_TYPE 				= 'ULNG',
	B_USHORT_TYPE 				= 'USHT'
};

extern const unsigned char B_HAND_CURSOR[];
extern const unsigned char B_I_BEAM_CURSOR[];

#endif
