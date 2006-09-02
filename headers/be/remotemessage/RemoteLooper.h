#ifndef REMOTELOOPER_H
#define REMOTELOOPER_H

// -------------------------------------------------------------------------------
/* 
	RemoteLooper
	 
	Copyright (c) 2001 Be Inc. All Rights Reserved. 
	 
	Author:	Alan Ellis 
			October 30, 2001 
 
	(Mostly) Abstract base class for remote Message recieving. 
*/ 
// -------------------------------------------------------------------------------

#include <OS.h> // thread_id

class BMessenger;
class BMessage;

class BRemoteLooper
{
	public:
							BRemoteLooper();
		
		virtual thread_id	Run() = 0;
		
		// Subclasses need to implement this to delete the class...
		virtual	void		Quit() = 0;

		// This is useful if you don't want to -have- to derive from this class to
		// use it, all Messages this class gets will be sent to the messenger.
				void		SetNotificationMessenger(BMessenger& Messenger);
		
		virtual	void		MessageReceived(BMessage* Message);

	protected:
		virtual				~BRemoteLooper() { }
		
	private:
		BMessenger* fMessenger;
};


#endif

