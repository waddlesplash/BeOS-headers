// ---------------------------------------------------------------------------------------- 
/* 
	SpyDisplayView.h 
	 
	Copyright (c) 2000 Be Inc. All Rights Reserved. 
	 
	Author:	Alan Ellis 
			December 22, 2000
 
	Base class for Spy-O-Matic display views. 
*/ 
// ----------------------------------------------------------------------------------------
#ifndef SPYDISPLAYVIEW_H
#define SPYDISPLAYVIEW_H

#include <View.h>

#include <be_apps/Spy/SpyComm.h>

class BSpyDisplayView : public BView
{
	public:
						BSpyDisplayView(const char* Name,
						                uint32 Flags =  B_WILL_DRAW | B_FRAME_EVENTS,
						                uint32 ResizeMask = B_FOLLOW_ALL);
						BSpyDisplayView(BRect Frame,
										const char *Name,
										uint32 ResizeMask,
										uint32 Flags);

		virtual			~BSpyDisplayView();
		
		virtual void	MessageReceived(BMessage* Message);
		virtual void	AttachedToWindow();
		virtual void	DetachedFromWindow();

				void	SendRemoteMessage(BMessage* Message, const char* TargetID = NULL);
				void	ReplyToMessage(BMessage* ReplyTo, BMessage* WithThis);		

				void	SubscribeTo(uint32 MessageConstant);
				void	UnsubscribeFrom(uint32 MessageConstant);
		
	protected:
		virtual void	SubscriptionReceived(BMessage* Message);	

	private:
		BSpyComm				fSpyCommUplink;
};

#endif

