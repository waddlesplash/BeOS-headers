//****************************************************************************
//
//	File:			FilePanel.h
//
//  Description:    BFilePanel and BRefFilter classes, and 
//					run_open_panel()/run_save_panel functions.
//
//	Copyright 1997, Be Incorporated, All Rights Reserved.
//
//****************************************************************************

#ifndef	_FILE_PANEL_H
#define _FILE_PANEL_H

#include	<sys/stat.h>
#include	<Entry.h>
#include	<Directory.h>
#include	<Node.h>

#pragma export on


/*- Old fashioned, one-shot, heavily-defaulted panel functions. -*/ 

extern void run_open_panel();
extern void run_save_panel();


/*---BRefFilter--------------------------------------------------*/

/* BRefFilter is used by BFilePanel.  Every time the user selects
 * an item in a file panel, the Filter() func is sent to the
 * panel's BRefFilter object.  Filter()'s return value determines
 * whether the item is admitted into the panel's list of 
 * displayed items.  Optional.
 */
class BRefFilter {
public:
virtual	bool	Filter(const entry_ref*, BNode*, struct stat*,
					   const char* mimetype) = 0;
};


/*---File Panel constants etc------------------------------------*/

enum file_panel_mode {
	B_OPEN_PANEL,
	B_SAVE_PANEL
};

enum file_panel_button {
	B_CANCEL_BUTTON,
	B_DEFAULT_BUTTON
};

class BWindow;
class BMessenger;
class BMessage;

/*---------------------------------------------------------------*/
/*----BFilePanel-------------------------------------------------*/

/* Most of the contructor parameters can also be set through individual
 * funcs.  But these can't:
 *
 *  file_panel_mode mode 
 *  uint32 node_flavors
 *  bool modal
 */

class BFilePanel {

public:
						BFilePanel(file_panel_mode mode = B_OPEN_PANEL,
							BMessenger* target = NULL,
							entry_ref *start_directory = NULL,
							uint32 node_flavors = 0,
							bool allow_multiple_selection = true,
							BMessage *message = NULL, 
							BRefFilter* = NULL,
							bool modal = false,
							bool hide_when_done = true);

virtual					~BFilePanel();

		void			Show();
		void			Hide();
		bool			IsShowing() const;

virtual	void			WasHidden();
virtual	void			SelectionChanged();
virtual	void			SendMessage(const BMessenger*, BMessage*);

		BWindow*		Window() const;
		BMessenger		Messenger() const;
		BRefFilter*		RefFilter() const;
		void			GetPanelDirectory(entry_ref*) const;

		file_panel_mode	PanelMode() const;

		void			SetTarget(BMessenger);
		void			SetMessage(BMessage *msg);

		void			SetRefFilter(BRefFilter* filter);
		void			SetSaveText(const char* text);
		void			SetButtonLabel(file_panel_button, const char* label);

		void			SetPanelDirectory(BEntry* new_directory);
		void			SetPanelDirectory(BDirectory* new_directory);
		void			SetPanelDirectory(entry_ref* new_directory);
		void 			SetPanelDirectory(const char *new_directory);

		void			SetHideWhenDone(bool);
		bool			HidesWhenDone(void) const;

		void			Refresh();
		void			Rewind();
		status_t		GetNextSelectedRef(entry_ref*);

private:
		BWindow*		fWindow;
};

#pragma export reset

#endif
