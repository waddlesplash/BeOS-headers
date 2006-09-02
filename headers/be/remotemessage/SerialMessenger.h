// -------------------------------------------------------------------------------
/* 
	SerialMessenger
	 
	Copyright (c) 2001 Be Inc. All Rights Reserved. 
	 
	Author:	Alan Ellis 
			October 24, 2001 
 
	Allows sending messages over a Serial port. 
*/ 
// -------------------------------------------------------------------------------
#ifndef SERIALMESSENGER_H
#define SERIALMESSENGER_H

#include <String.h>

#include <remotemessage/RemoteMessenger.h>

class BSerialTransport;

class BSerialMessenger : public BRemoteMessenger
{
	public:
									BSerialMessenger(const BString& Port = BString("serial1"));
									~BSerialMessenger();
							
						status_t	SendMessage(const BMessage& Message) const;
		virtual			bool		IsValid() const;
		virtual	const	BString		Target() const;
			
	private:
		BSerialTransport*	fTransport;
	
};

#endif

