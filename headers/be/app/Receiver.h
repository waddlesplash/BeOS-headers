//******************************************************************************
//
//	File:			Receiver.h
//
//	Description:	Client receiver class.
//
//	Copyright 1995-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef _RECEIVER_H
#define _RECEIVER_H

#ifndef _OBJECT_H
#include <Object.h>
#endif
#ifndef _MESSAGE_H
#include <Message.h>
#endif

class BLooper;

class BReceiver : public BObject {
	B_DECLARE_CLASS_INFO(BObject);

public:
				BReceiver();
virtual			~BReceiver();

virtual	void	MessageReceived(BMessage *message);
virtual	BLooper	*Looper() const;

protected:

private:
friend inline long _get_object_token_(const BReceiver *);

		long	fToken;
};

#endif
