// -------------------------------------------------------------------------------
/* 
	SerialLooper
	 
	Copyright (c) 2001 Be Inc. All Rights Reserved. 
	 
	Author:	Alan Ellis 
			October 24, 2001 
 
	Allows receiving messages over a Serial port. This is really more like a
	handler than a Looper ... oh well.
*/ 
// -------------------------------------------------------------------------------
#ifndef SERIALLOOPER_H
#define SERIALLOOPER_H

#include <String.h>
#include <remotemessage/RemoteLooper.h>

class BSerialTransport;

class BSerialLooper : public BRemoteLooper
{
	public:
									BSerialLooper(const BString& Port = BString("serial1"));
		
		virtual			status_t	Run();
		virtual			void		Quit();
		virtual			void		MessageReceived(BMessage* Message);
						void		DetachMessage();
				
				const	BString		Port() const; 
	protected:	
		virtual						~BSerialLooper();

	private:
		BSerialTransport*	fTransport;
};


#endif

