/*
  -----------------------------------------------------------------------------

	File:			LayoutUtils.h
	
	Description:	Helper functions to align MenuFields
	
	Copyright 2004, Yellow Tab GmbH, All rights reserved.

  -----------------------------------------------------------------------------
*/

#ifndef _LAYOUT_UTILS_H_
#define _LAYOUT_UTILS_H_

#include <experimental/SafeArray.h>
#include <interface/InterfaceDefs.h>

class BMenuField;

namespace Z {
namespace Interface {

// Center the dividers on the MenuFields. 
// All fields will be the same dimenstions after processing.
void center_align_menufields(const Z::Experimental::Support::BSafeArray<BMenuField*>& _fields, alignment _alignment = B_ALIGN_RIGHT);

// Stack them in a font sensitive manner.
// First MenuField is the left top basis, all others will be stacked
//  vertically under in order of thier list index.
void vertically_space_menufields(const Z::Experimental::Support::BSafeArray<BMenuField*>& _fields);

} 	// Interface
} 	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Interface::center_align_menufields;
using Z::Interface::vertically_space_menufields;
#endif

#endif
