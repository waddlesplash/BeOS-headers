/*
  -----------------------------------------------------------------------------

	File: sys_apps/Tracker/Icons.h
	
	Description: Preliminary interface for getting Tracker icons. 
	
	            *******
	            WARNING
	            *******
	            
	            This is preliminary API, and may change or go away as such.
	            
	
	Copyright 2003, 2004, yellowTAB GmbH, All rights reserved.

  -----------------------------------------------------------------------------
*/

#ifndef _TRACKER_ICONS_H
#define _TRACKER_ICONS_H

#include <posix/be_prim.h>

class BBitmap;
class BEntry;

namespace Z {
namespace Tracker {
	
const BBitmap& GetTrackerIcon(const char* MimeString, uint32 IconSize);
const BBitmap& GetTrackerIcon(const BEntry& Entry, uint32 IconSize);

} // Tracker 
} // Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
	using namespace Z::Tracker;
#endif

#endif
