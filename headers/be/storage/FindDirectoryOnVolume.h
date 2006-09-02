/* 
	Copyright 2002-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the NewOS License.

	Part of PnP driver system
	
	
	Special version of find_directory that works on _all_
	volumes.
*/

#ifndef _FIND_DIRECTORY_ON_VOLUME
#define _FIND_DIRECTORY_ON_VOLUME

#include <FindDirectory.h>

status_t find_directory_on_volume( 
	directory_which which, BPath *path, bool and_create_it, BVolume *volume );
	
#endif
