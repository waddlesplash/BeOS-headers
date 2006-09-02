/*
  -----------------------------------------------------------------------------

	File: BitmapTool.h
	
	Description: A bitmap displaying tool including label support.
	
	
	Copyright 2006, yellowTAB GmbH, All rights reserved.
	

  -----------------------------------------------------------------------------
*/

#ifndef _BITMAPTOOL_H_
#define _BITMAPTOOL_H_

#include "experimental/StringTool.h"

#include <interface/Bitmap.h>
#include <support/String.h>

namespace Z {
namespace Experimental {
namespace Interface {

class BBitmapTool : public BStringTool
{
	public :
									BBitmapTool(
										const BString _name,
										BBitmap* _bitmap,
										const BString _string,
										BMessage* _message = NULL ,
										bool _no_label = false, 
										nu_button_style = BS_PLAIN_BUTTON);
									
		virtual						~BBitmapTool();

				BBitmap&			Bitmap() const;

		virtual void				Draw(
										BRect _update_rect );
		
		virtual void				GetPreferredSize(
										float* _width,
										float* _height );
		
		virtual void				ResizeToPreferred();
		
				void				SetBitmap(
										BBitmap* _bitmap );

	private :
				void				BuildDisabledBitmap();
				
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
				BBitmap*			fBitmap;
				BBitmap*			fDisabledBitmap;
				
				uint32				_ReservedData[ 10 ];
};

} // ns Interface
} // ns Experimental
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BBitmapTool;
#endif

#endif /* _BITMAPTOOL_H_ */
