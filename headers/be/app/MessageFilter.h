//******************************************************************************
//
//	File:			MessageFilter.h
//
//	Copyright 1996-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************


#ifndef _MESSAGE_FILTER_H
#define _MESSAGE_FILTER_H

#include <Handler.h>

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

class BHandler;
class BMessage;

/*-------------------------------------------------------------*/

typedef filter_result (*filter_hook)
	(BMessage *message, BHandler **target, BMessageFilter *filter);

class BMessageFilter {

public:
							BMessageFilter(	uint32 what,
											filter_hook func = NULL);
							BMessageFilter(	message_delivery delivery,
											message_source source,
											filter_hook func = NULL);
							BMessageFilter(	message_delivery delivery,
											message_source source,
											uint32 what,
											filter_hook func = NULL);
							BMessageFilter(const BMessageFilter &filter);
							BMessageFilter(const BMessageFilter *filter);
virtual						~BMessageFilter();

		BMessageFilter		&operator=(const BMessageFilter &from);

virtual	filter_result		Filter(BMessage *message, BHandler **target);

		message_delivery	MessageDelivery() const;
		message_source		MessageSource() const;
		uint32				Command() const;
		bool				FiltersAnyCommand() const;
		BLooper				*Looper() const;

private:
friend	class BLooper;

virtual	void			_ReservedMessageFilter1();
virtual	void			_ReservedMessageFilter2();

		void				SetLooper(BLooper *owner);
		filter_hook			FilterFunction() const;
		bool				fFiltersAny;
		uint32				what;
		message_delivery	fDelivery;
		message_source		fSource;
		BLooper				*fLooper;
		filter_hook			fFilterFunction;
		uint32				_reserved[3];
};

#endif
