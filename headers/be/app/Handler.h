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

class BHandler : public BObject {
	B_DECLARE_CLASS_INFO(BObject);

public:
					BHandler(const char *name = NULL);
virtual				~BHandler();

virtual	void		MessageReceived(BMessage *message);
virtual	void		HandlersRequested(BMessage *msg);
		BLooper		*Looper() const;

		const char	*Name() const;
		void		SetName(const char *name);

private:
friend inline long _get_object_token_(const BHandler *);
friend inline BLooper *_get_handler_looper_(const BHandler *);
friend class BLooper;

		long		fToken;
		char		*fName;
		BLooper		*fLooper;
};

#endif
