/*
	
	MenuBar.h
	
	Copyright 1994-96 Be, Inc. All Rights Reserved.
	
*/

#ifndef _MENU_BAR_H
#define _MENU_BAR_H

#ifndef _INTERFACE_DEFS_H
#include <InterfaceDefs.h>
#endif
#ifndef _MENU_H
#include "Menu.h"
#endif
#ifndef _OS_H
#include <OS.h>
#endif

#define B_MENU_BAR_HEIGHT	15.0

enum {
	B_BORDER_FRAME = 0x01,
	B_BORDER_CONTENTS = 0x02,
	B_BORDER_EACH_ITEM = 0x04
};

class BMenu;
class BWindow;
class BMenuItem;

class BMenuBar : public BMenu
{
		B_DECLARE_CLASS_INFO(BMenu);
public:

/* Public Interface for clients of this class */

					BMenuBar(	BRect frame,
								const char *title,
								ulong resizeMask =
									B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP,
								menu_layout layout = B_ITEMS_IN_ROW,
								bool resizeToFit = TRUE);
virtual				~BMenuBar();

/* Public Interface for derived classes and partner classes */

		void		SetBorder(ulong border);
virtual	void		Draw(BRect updateRect);
virtual void		AttachedToWindow();
virtual	void		MouseDown(BPoint where);

private:
friend BWindow;
friend BMenuItem;

		void		StartMenuBar(long menuIndex, bool sticky = TRUE);
static	long		TrackTask(void *arg);
		BMenuItem	*Track(int *action, long startIndex = -1);
		void		RestoreFocus();
		void		RedrawAfterSticky(BRect bounds);
		void		SetStickyEnabled(bool state);
		void		SetPopUpMenuBar(bool state);
		bool		AllowSticky();
		
		ulong		fBorder;
		thread_id	fTrackingPID;
		bool		fAllowSticky;
		bool		fPopUpMenuBar;
		bool		fTracking;
		long		fPrevFocusToken;
		sem_id		fMenuSem;
};

#endif
