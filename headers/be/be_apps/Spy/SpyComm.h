// --------------------------------------------------------------------------- 
/* 
	SpyComm.h 
	 
	Copyright (c) 2000 Be Inc. All Rights Reserved. 
	 
	Author:	Alan Ellis 
			December 1, 2000 
 
	Remote Communications class for Spy-O-Matic  
*/ 
// --------------------------------------------------------------------------- 
#ifndef SPYCOMM_H
#define SPYCOMM_H

#include <String.h>

class BHandler;
class BMessage;

class BSpyComm
{
	public:
							BSpyComm(BHandler& Handler);
		virtual				~BSpyComm();
		
				void		SubscribeTo(uint32 MessageConstant);
				void		UnsubscribeFrom(uint32 MessageConstant);
				
				void		SendRemoteMessage(BMessage* Message,
							                  const char* TargetID = NULL);
				void		ReplyToMessage(BMessage* ReplyTo, BMessage* WithThis);		
				
	protected:
	
	private:
		BHandler&	fHandler;
};

#endif

