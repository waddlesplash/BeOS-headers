//******************************************************************************
//
//	File:		BInvoker.h
//
//	Description:	a class for objects that post messages
//
//	Copyright 1993-97, Be Incorporated
//
//******************************************************************************
 
#pragma once

#ifndef	_INVOKER_H
#define	_INVOKER_H

#include <Message.h>
#include <Messenger.h>
#include <Handler.h>
#include <Looper.h>

//------------------------------------------------------------------------------

class BInvoker {
public:
					BInvoker(); 
					BInvoker(BMessage *message,
							 const BHandler *handler,
							 const BLooper *looper = NULL);
					BInvoker(BMessage *message, BMessenger target);
virtual				~BInvoker();

virtual	status_t	SetMessage(BMessage *message);
		BMessage	*Message() const;
		uint32		Command() const;

virtual status_t	SetTarget(const BHandler *h, const BLooper *loop = NULL);
virtual status_t	SetTarget(BMessenger messenger);
		bool		IsTargetLocal() const;
		BHandler	*Target(BLooper **looper = NULL) const;
		BMessenger	Messenger() const;

virtual status_t	SetHandlerForReply(BHandler *handler);
		BHandler	*HandlerForReply() const;

virtual	status_t	Invoke(BMessage *msg = NULL);

private:

virtual	void		_ReservedInvoker1();
virtual	void		_ReservedInvoker2();
virtual	void		_ReservedInvoker3();

					BInvoker(const BInvoker &);
		BInvoker	&operator=(const BInvoker &);

		BMessage	*fMessage;
		BMessenger	fMessenger;
		BHandler	*fReplyTo;
		uint32		_reserved[4];
};

//------------------------------------------------------------------------------

#endif
