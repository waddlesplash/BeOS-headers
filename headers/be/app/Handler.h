//******************************************************************************
//
//	File:			Handler.h
//
//	Description:	Client handler class.
//
//	Copyright 1995-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef _HANDLER_H
#define _HANDLER_H

#ifndef _OBJECT_H
#include <Object.h>
#endif
#ifndef _MESSAGE_H
#include <Message.h>
#endif

class BLooper;
class BMessageFilter;
class BList;

class BHandler : public BObject {

public:
					BHandler(const char *name = NULL);
virtual				~BHandler();

virtual	void		MessageReceived(BMessage *message);
virtual	void		HandlersRequested(BMessage *msg);
		BLooper		*Looper() const;

		const char	*Name() const;
		void		SetName(const char *name);

virtual	void		SetNextHandler(BHandler *handler);
		BHandler	*NextHandler() const;

virtual	void		AddFilter(BMessageFilter *filter);
virtual	bool		RemoveFilter(BMessageFilter *filter);
virtual	void		SetFilterList(BList *filters);
		BList		*FilterList();

private:
friend inline long _get_object_token_(const BHandler *);
friend inline BLooper *_get_handler_looper_(const BHandler *);
friend class BLooper;
friend class BMessageFilter;

		long		fToken;
		char		*fName;
		BLooper		*fLooper;
		BHandler	*fNextHandler;
		BList		*fFilters;
};

#endif
