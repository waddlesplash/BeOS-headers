// ----------------------------------------------------------------------------------------------- 
/* 
	SpyDisplayModule 
	 
	Copyright (c) 2001 Be Inc. All Rights Reserved. 
	 
	Author:	Alan Ellis 
			December 10, 2000 
 
	Abstract base class for SpyModules, provides a little functionality. 
*/ 
// ----------------------------------------------------------------------------------------------- 
#ifndef SPYDISPLAYMODULE_H
#define SPYDISPLAYMODULE_H

#include <vector> 


#include <be_apps/Spy/SpyModule.h>

class BSpyDisplayModule : public BSpyModule
{
	public:
								BSpyDisplayModule(const char* Name);
		virtual					~BSpyDisplayModule();
		
		virtual BView*			CreateView() = 0;
		
		virtual	void			AttachedToLooper();
		virtual void			MessageReceived(BMessage* Message);
		
	protected:
		virtual void			SubscriptionReceived(BMessage* Message);
	
	private:
				void			HandleViewRequest(BMessage* Message);
				
};


#endif

