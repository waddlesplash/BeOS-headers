/*
  -----------------------------------------------------------------------------

	File: StringTool.h
	
	Description: A string tool.
	
	
	Copyright 2006, yellowTAB GmbH, All rights reserved.
	

  -----------------------------------------------------------------------------
*/

#ifndef _STRINGTOOL_H_
#define _STRINGTOOL_H_

#include "experimental/Tool.h"

#include <support/String.h>

namespace Z {
namespace Experimental {
namespace Interface {

class BStringTool : public BTool
{
	public :
									BStringTool(
										const BString _name,
										const BString _string,
										BMessage* _message = NULL, 
										nu_button_style = BS_PLAIN_BUTTON);
									
		virtual						~BStringTool();

		virtual void				Draw(
										BRect _update_rect );
		
		virtual void				GetPreferredSize(
										float* _width,
										float* _height );
		
		virtual void				ResizeToPreferred();

				void				SetString(
										const BString _string );

		const	char*				String() const;

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
				BString				fString;
				
				uint32				_ReservedData[ 10 ];
};

} // ns Interface
} // ns Experimental
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BStringTool;
#endif

#endif /* _STRINGTOOL_H_ */
