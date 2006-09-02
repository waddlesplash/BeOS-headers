/*
  -----------------------------------------------------------------------------

	File: Tool.h
	
	Description: A tool base class.
	
	
	Copyright 2006, yellowTAB GmbH, All rights reserved.
	

  -----------------------------------------------------------------------------
*/

#ifndef _TOOL_H_
#define _TOOL_H_

#include <interface/Control.h>
#include <interface/Insets.h>

class BPopUpMenu;

namespace Z {
namespace Experimental {
namespace Interface {
	
enum nu_button_style
{
	BS_NO_BUTTON,
	BS_PLAIN_BUTTON
};

class BTool : public BControl
{
	public :
									BTool(
										const BString _name,
										BMessage* _message = NULL,
										nu_button_style = BS_PLAIN_BUTTON);
									
		virtual						~BTool();

		virtual void				AttachedToWindow();

		virtual void				Draw(
										BRect _update_rect );
		
				BInsets				FrameInset() const;
		
		virtual void				GetPreferredSize(
										float* _width,
										float* _height );

		virtual void				MouseDown(
										BPoint _where );
										
		virtual void				MouseMoved(
										BPoint _where,
										uint32 _transit,
										const BMessage* _message );

		virtual void				MouseUp(
										BPoint _where );

		virtual void				ResizeToPreferred();
		
				void				SetButtonStyle(nu_button_style);
				
	nu_button_style					ButtonStyle();
	
				void				SetDropMenu(BPopUpMenu* drop_menu);
				
		 BPopUpMenu*				DropMenu() const;
	private :
		virtual void				_ReservedMethod1();
		virtual void				_ReservedMethod2();
		virtual void				_ReservedMethod3();
		virtual void				_ReservedMethod4();
		virtual void				_ReservedMethod5();
		virtual void				_ReservedMethod6();
		virtual void				_ReservedMethod7();
		virtual void				_ReservedMethod8();
		virtual void				_ReservedMethod9();
		virtual void				_ReservedMethod10();

	private :
				bool				fOver;
		nu_button_style				fButtonStyle;
			BPopUpMenu*				fDropMenu;
			
				uint32				_ReservedData[ 10 ];
};

} // ns Interface
} // ns Experimental
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BTool;
using Z::Experimental::Interface::nu_button_style;
using Z::Experimental::Interface::BS_NO_BUTTON;
using Z::Experimental::Interface::BS_PLAIN_BUTTON;
#endif

#endif /* _TOOL_H_ */
