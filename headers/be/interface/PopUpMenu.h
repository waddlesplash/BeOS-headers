/*
	
	PopUpMenu.h
	
	Copyright 1994 Be, Inc. All Rights Reserved.
	
*/

#ifndef _POP_UP_MENU_H
#define _POP_UP_MENU_H

#ifndef _MENU_H
#include <interface/Menu.h>
#endif

class BPopUpMenu : public BMenu
{
	DECLARE_CLASS_INFO(BMenu);
public:
					BPopUpMenu(	const char *title,
								bool radioMode = TRUE,
								bool autoRename = TRUE,
								menu_layout layout = ITEMS_IN_COLUMN
								);
virtual				~BPopUpMenu();
		BMenuItem	*Run(BPoint where);

protected:
virtual	BPoint		ScreenLocation();

private:
		BPoint		fWhere;
		bool		fUseWhere;
};

#endif
