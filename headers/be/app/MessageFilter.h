//******************************************************************************
//
//	File:			MessageFilter.h
//
//	Copyright 1996, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef _MESSAGE_FILTER_H
#define _MESSAGE_FILTER_H

#ifndef _OBJECT_H
#include <Object.h>
#endif
#ifndef _HANDLER_H
#include <Handler.h>
#endif

/*-------------------------------------------------------------*/

enum filter_result {
	B_SKIP_MESSAGE,
	B_DISPATCH_MESSAGE
};

enum message_delivery {
	B_ANY_DELIVERY,
	B_DROPPED_DELIVERY,
	B_PROGRAMMED_DELIVERY
};

enum message_source {
	B_ANY_SOURCE,
	B_REMOTE_SOURCE,
	B_LOCAL_SOURCE
};

/*-------------------------------------------------------------*/

class BMessageFilter : public BObject {

public:
							BMessageFilter(	message_delivery delivery,
											message_source source);
							BMessageFilter(	message_delivery delivery,
											message_source source,
											ulong what);
virtual						~BMessageFilter();

virtual	filter_result		Filter(BMessage *message, BHandler **target);

		message_delivery	MessageDelivery();
		message_source		MessageSource();
		ulong				Command();
		bool				FiltersAnyCommand();

private:

		bool				fFiltersAny;
		ulong				what;
		message_delivery	fDelivery;
		message_source		fSource;
};

/*-------------------------------------------------------------*/

inline message_delivery BMessageFilter::MessageDelivery()
	{ return fDelivery; };

/*-------------------------------------------------------------*/

inline message_source BMessageFilter::MessageSource()
	{ return fSource; };

/*-------------------------------------------------------------*/

inline ulong BMessageFilter::Command()
	{ return what; };

/*-------------------------------------------------------------*/

inline bool BMessageFilter::FiltersAnyCommand()
	{ return fFiltersAny; };

/*-------------------------------------------------------------*/

#endif
