/*
	
	MenuBar.h
	
	Copyright 1994-97 Be, Inc. All Rights Reserved.
	
*/


#ifndef _MENU_BAR_H
#define _MENU_BAR_H

#include <InterfaceDefs.h>
#include <Menu.h>
#include <OS.h>

enum menu_bar_border {
	B_BORDER_FRAME,
	B_BORDER_CONTENTS,
	B_BORDER_EACH_ITEM
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
									uint32 resizeMask =
										B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP,
									menu_layout layout = B_ITEMS_IN_ROW,
									bool resizeToFit = TRUE);
						BMenuBar(BMessage *data);
virtual					~BMenuBar();
static	BMenuBar		*Instantiate(BMessage *data);
virtual	status_t		Archive(BMessage *data, bool deep = true) const;

/* Public Interface for derived classes and partner classes */

virtual	void			SetBorder(menu_bar_border border);
		menu_bar_border	Border() const;
virtual	void			Draw(BRect updateRect);
virtual void			AttachedToWindow();
virtual	void			DetachedFromWindow();
virtual void			MessageReceived(BMessage *msg);
virtual	void			MouseDown(BPoint where);
virtual void			WindowActivated(bool state);
virtual	void			MouseUp(BPoint where);
virtual	void			FrameMoved(BPoint new_position);
virtual	void			FrameResized(float new_width, float new_height);

virtual void			Show();
virtual void			Hide();

virtual BHandler		*ResolveSpecifier(BMessage *msg,
										int32 index,
										BMessage *specifier,
										int32 form,
										const char *property);
virtual status_t		GetSupportedSuites(BMessage *data);
virtual status_t		Perform(uint32 d, void *arg);

private:
friend BWindow;
friend BMenuItem;
friend BMenuField;

virtual	void			_ReservedMenuBar1();
virtual	void			_ReservedMenuBar2();
virtual	void			_ReservedMenuBar3();
virtual	void			_ReservedMenuBar4();

		BMenuBar		&operator=(const BMenuBar &);

		void			StartMenuBar(	int32 menuIndex,
										bool sticky = TRUE,
										bool show_menu = FALSE,
										BRect *special_rect = NULL);
static	long			TrackTask(void *arg);
		BMenuItem		*Track(	int32 *action,
								int32 startIndex = -1,
								bool showMenu = FALSE);
		void			RestoreFocus();
		void			InitData(menu_layout layout);
		
		menu_bar_border	fBorder;
		thread_id		fTrackingPID;
		int32			fPrevFocusToken;
		sem_id			fMenuSem;
		uint32			_reserved[3];

		bool			fTracking;
};

#endif
