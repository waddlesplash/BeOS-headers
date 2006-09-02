#ifndef REMOTEMESSENGER_H
#define REMOTEMESSENGER_H

// -------------------------------------------------------------------------------
/* 
	RemoteMessenger
	 
	Copyright (c) 2001 Be Inc. All Rights Reserved. 
	 
	Author:	Alan Ellis 
			October 30, 2001 
 
	Abstract base class for semding Messages to remote Loopers. 
*/ 
// -------------------------------------------------------------------------------

#include <be_prim.h> // status_t

class BString;

class BRemoteMessenger
{
	public:
									BRemoteMessenger() { }
		virtual						~BRemoteMessenger() { }
		
		virtual		 	status_t	SendMessage(const BMessage& Message) const = 0;
		virtual			bool		IsValid() const = 0;
		virtual	const	BString		Target() const = 0;
};

#endif

