// --------------------------------------------------------------------------- 
/* 
	SpyModule.cpp 
	 
	Copyright (c) 2000 Be Inc. All Rights Reserved. 
	 
	Author:	Alan Ellis 
			December 1, 2000 
 
	Base Module class for the CommandModule class to use. 
*/ 
// --------------------------------------------------------------------------- 
#ifndef SPYMODULE_H
#define SPYMODULE_H

#include <String.h>
#include <Handler.h>

#include <be_apps/Spy/SpyComm.h>
								
class BSpyModule : public BHandler
{
	public:
						BSpyModule(const char* Name);
		virtual			~BSpyModule();
	
		virtual void	AttachedToLooper() = 0;
		virtual void	MessageReceived(BMessage* Message);
		
	protected:
		virtual void	SubscriptionReceived(BMessage* Message) = 0;	

				void	SendRemoteMessage(BMessage* Message, const char* TargetID = NULL);
				void	ReplyToMessage(BMessage* ReplyTo, BMessage* WithThis);		

				void	SubscribeTo(uint32 MessageConstant);
				void	UnsubscribeFrom(uint32 MessageConstant);
	
	private:
		BSpyComm	fSpyCommUplink;

};

#endif

