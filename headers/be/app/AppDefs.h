/******************************************************************************

	File:			AppDefs.h

	Description:	Some common type definitions.

	Copyright 1993-97, Be Incorporated

******************************************************************************/

#pragma once
#ifndef _APP_DEFS_H
#define _APP_DEFS_H

#include <SupportDefs.h>
#include <TypeConstants.h>


/* System Message codes */
enum {
	B_ABOUT_REQUESTED		= '_ABR',
	B_WINDOW_ACTIVATED		= '_ACT',
	B_APP_ACTIVATED			= '_ACT',	/* ## SAME AS B_WINDOW_ACTIVATED ## */
	B_ARGV_RECEIVED 		= '_ARG',
	B_QUIT_REQUESTED 		= '_QRQ',
	B_CLOSE_REQUESTED 		= '_QRQ',	/* ## SAME AS B_QUIT_REQUESTED ## */
	B_CANCEL				= '_CNC',
	B_KEY_DOWN 				= '_KYD',
	B_KEY_UP 				= '_KYU',
	B_MINIMIZE				= '_WMN',
	B_MOUSE_DOWN 			= '_MDN',
	B_MOUSE_MOVED 			= '_MMV',
	B_MOUSE_ENTER_EXIT		= '_MEX',
	B_MOUSE_UP 				= '_MUP',
	B_PULSE 				= '_PUL',
	B_READY_TO_RUN 			= '_RTR',
	B_REFS_RECEIVED 		= '_RRC',
	B_SCREEN_CHANGED 		= '_SCH',
	B_VALUE_CHANGED 		= '_VCH',
	B_VIEW_MOVED 			= '_VMV',
	B_VIEW_RESIZED 			= '_VRS',
	B_WINDOW_MOVED 			= '_WMV',
	B_WINDOW_RESIZED 		= '_WRS',
	B_WORKSPACES_CHANGED	= '_WCG',
	B_WORKSPACE_ACTIVATED	= '_WAC',
	B_ZOOM					= '_WZM',
	_APP_MENU_				= '_AMN',
	_BROWSER_MENUS_			= '_BRM',
	_MENU_EVENT_ 			= '_MEV',
	_SAVE_PACKAGE_			= '_SVP',
	_PULSE_ENABLED_			= '_PBL',
	_QUIT_ 					= '_QIT',
	_VOLUME_MOUNTED_ 		= '_NVL',
	_VOLUME_UNMOUNTED_		= '_VRM',
	_OPEN_IN_WORKSPACE_		= '_OWS',
	_MESSAGE_DROPPED_ 		= '_MDP',
	_MENUS_DONE_			= '_MND',
	_SHOW_DRAG_HANDLES_		= '_SDH'
};

/* other commands */
enum {
	B_SET_PROPERTY				= 'PSET',
	B_GET_PROPERTY				= 'PGET',
	B_CREATE_PROPERTY			= 'PCRT',
	B_DELETE_PROPERTY			= 'PDEL',
	B_GET_SUPPORTED_SUITES		= 'SUIT',
	B_CUT 						= 'CCUT',
	B_COPY 						= 'COPY',
	B_PASTE 					= 'PSTE',
	B_SELECT_ALL				= 'SALL',
	B_SAVE_REQUESTED 			= 'SAVE',
	B_MESSAGE_NOT_UNDERSTOOD	= 'MNOT',
	B_NO_REPLY 					= 'NONE',
	B_REPLY 					= 'RPLY',
	B_SIMPLE_DATA				= 'DATA',
	B_MIME_DATA					= 'MIME',
	B_ARCHIVED_OBJECT			= 'ARCV',
	B_UPDATE_STATUS_BAR			= 'SBUP',
	B_RESET_STATUS_BAR			= 'SBRS',
	B_NODE_MONITOR				= 'NDMN',
	B_QUERY_UPDATE				= 'QUPD'
};

extern const unsigned char B_HAND_CURSOR[];
extern const unsigned char B_I_BEAM_CURSOR[];

#endif
