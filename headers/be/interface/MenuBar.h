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

enum menu_bar_border {
	B_BORDER_FRAME = 0x01,
	B_BORDER_CONTENTS = 0x02,
	B_BORDER_EACH_ITEM = 0x04
};

class BMenu;
class BWindow;
class BMenuItem;
class BMenuField;

class BMenuBar : public BMenu
{
public:

/* Public Interface for clients of this class */

						BMenuBar(	BRect frame,
									const char *title,
									ulong resizeMask =
										B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP,
									menu_layout layout = B_ITEMS_IN_ROW,
									bool resizeToFit = TRUE);
virtual					~BMenuBar();

/* Public Interface for derived classes and partner classes */

virtual	void			SetBorder(menu_bar_border border);
		menu_bar_border	Border() const;
virtual	void			Draw(BRect updateRect);
virtual void			AttachedToWindow();
virtual	void			MouseDown(BPoint where);

private:
friend BWindow;
friend BMenuItem;
friend BMenuField;

		void			StartMenuBar(	long menuIndex,
										bool sticky = TRUE,
										bool show_menu = FALSE,
										BRect *special_rect = NULL);
static	long			TrackTask(void *arg);
		BMenuItem		*Track(	int *action,
								long startIndex = -1,
								bool showMenu = FALSE);
		void			RestoreFocus();
		
		menu_bar_border	fBorder;
		thread_id		fTrackingPID;
		bool			fTracking;
		long			fPrevFocusToken;
		sem_id			fMenuSem;
};

#endif
