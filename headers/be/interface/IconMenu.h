#ifndef _ICONMENU_H
#define _ICONMENU_H

/* 
 * The contents of this file are subject to the Mozilla Public 
 * License Version 1.1 (the "License"); you may not use this file 
 * except in compliance with the License. You may obtain a copy of 
 * the License at http://www.mozilla.org/MPL/ 
 * 
 * Software distributed under the License is distributed on an "AS 
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or 
 * implied. See the License for the specific language governing 
 * rights and limitations under the License. 
 * 
 * The Original Code is Vision.
 * 
 * The Initial Developer of the Original Code is The Vision Team.
 * Portions created by The Vision Team are
 * Copyright (C) 1999, 2000, 2001 The Vision Team.  All Rights
 * Reserved.
 * 
 * Contributor(s): Rene Gollent
 *                 Alan Ellis <alan@cgsoftware.org>
 */

//------------------------------------------------------------------------------
// IconMenu.h
//------------------------------------------------------------------------------
// A menu item implementation that displays an icon as its label.
//
// IconMenu implementation Copyright (C) 1998 Tyler Riti <fizzboy@mail.utexas.edu>
// Based on code Copyright (C) 1997 Jens Kilian
// This code is free to use in any way so long as the credits above remain intact.
// This code carries no warranties or guarantees of any kind. Use at your own risk.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// I N C L U D E S
//------------------------------------------------------------------------------

#include <be/interface/MenuItem.h>
#include <be/interface/Rect.h>

//------------------------------------------------------------------------------
// D E C L A R A T I O N S
//------------------------------------------------------------------------------

class BBitmap;

namespace Z {
namespace Interface {
	
class BIconMenu : public BMenuItem
{
public:
    // Constructor
    // Description:	Creates a menu item with the provided icon as its
    //				label and menu as its content.
    // Requires:		Both icon and menu must be valid.
    // Result:		If icon is valid, then the icon it points to will
    //				be used as the label for the menu. If icon is NULL
    //				then the menu's name will be used instead. If icon
    //				is invalid, a crash occurs. If menu is invalid or
    //				NULL, a crash occurs.
    // Notes:			Client code is still responsible for deleting the
    //				data icon points to. IconMenu only copies the data,
    //				it does not take posession of it.
	BIconMenu(BBitmap* icon, BMenu* menu);

    // Constructor
    // Description:	Creates a menu item with the application's mini
    //				icon as its label and menu as its content.
    // Requires:		A valid BMenu pointer. The application should also
    //				have a mini icon.
    // Result:		If the application's mini icon is found then the
    //				menu will be created with the icon as the label.
    //				Otherwise, the name of menu will be used as the
    //				label instead. If menu is invalid or NULL, a
    //				crash will occur.
	BIconMenu(BMenu* menu);

    // Destructor
    virtual ~BIconMenu();

protected:
    // Overridden Hook Functions
    virtual void GetContentSize(float* width, float* height);
    virtual void DrawContent();

private:
    // Disabled Copy Constructor
	BIconMenu(const BIconMenu& iconMenu);

    // Disabled Assignment Operator
	BIconMenu& operator=(const BIconMenu& iconMenu);

    BRect	bounds;
    BBitmap* iconLabel;
};

//---------------------------------------------------------------- IconMenu.h --

}	// Interaface
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Interface::BIconMenu;
#endif

#endif

