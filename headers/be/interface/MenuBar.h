/*
	
	MenuBar.h
	
	Copyright 1994 Be, Inc. All Rights Reserved.
	
*/

#ifndef _MENU_BAR_H
#define _MENU_BAR_H

#ifndef _INTERFACE_DEFS_H
#include <interface/InterfaceDefs.h>
#endif
#ifndef _MENU_H
#include "Menu.h"
#endif
#ifndef _OS_H
#include <os/OS.h>
#endif

enum {
	BORDER_FRAME = 0x01,
	BORDER_CONTENTS = 0x02,
	BORDER_EACH_ITEM = 0x04
};

class BMenu;
class BWindow;
class BMenuItem;

class BMenuBar : public BMenu
{
		DECLARE_CLASS_INFO(BMenu);
public:

/* Public Interface for clients of this class */

					BMenuBar(	BRect frame,
								const char *title,
								ulong resizeMask = FOLLOW_LEFT_TOP_RIGHT,
								menu_layout layout = ITEMS_IN_ROW,
								bool resizeToFit = FALSE);
virtual				~BMenuBar();

/* Public Interface for derived classes and partner classes */

		void		SetBorder(ulong border);
virtual	void		Draw(BRect updateRect);
virtual void		AttachedToWindow();
virtual	void		MouseDown(BPoint where);

private:
friend BWindow;

		void		StartMenuBar(long menuIndex, bool sticky = TRUE);
		void		SetAutoTrack(bool value);
static	void		TrackTask();
		BMenuItem	*Track(int *action, long startIndex = -1);
		
		ulong		fBorder;
		thread_id	fTrackingPID;
		bool		fTracking;
		bool		fTrackInSticky;
};

#endif
