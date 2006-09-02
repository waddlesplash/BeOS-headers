/*
  -----------------------------------------------------------------------------

	File: DividerTool.h
	
	Description: A string tool.
	
	
	Copyright 2006, yellowTAB GmbH, All rights reserved.
	

  -----------------------------------------------------------------------------
*/

#ifndef _DIVIDERTOOL_H_
#define _DIVIDERTOOL_H_

#include "experimental/Tool.h"

#include <support/String.h>

namespace Z {
namespace Experimental {
namespace Interface {

class BDividerTool : public BTool
{
	public :
									BDividerTool();
									
		virtual						~BDividerTool();

		virtual void				Draw(
										BRect _update_rect );
		
		virtual void				GetPreferredSize(
										float* _width,
										float* _height );
		
		virtual void				ResizeToPreferred();

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
				uint32				_ReservedData[ 10 ];
};

} // ns Interface
} // ns Experimental
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BDividerTool;
#endif

#endif /* _DIVIDERTOOL_H_ */
