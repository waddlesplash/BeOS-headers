//******************************************************************************
//
//	File:		MessageQueue.h
//
//	Description:	MessageQueue object.
//
//	Copyright 1993-96, Be Incorporated
//
//******************************************************************************

#ifndef	_MESSAGE_QUEUE_H
#define	_MESSAGE_QUEUE_H

#ifndef _MESSAGE_H
#include <Message.h>
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif
#ifndef _LOCKER_H
#include <Locker.h>
#endif

//------------------------------------------------------------------------------

class	BMessageQueue : BObject {

public:
					BMessageQueue();	
virtual				~BMessageQueue();

		void		AddMessage(BMessage *an_event);
		BMessage	*NextMessage();
		bool		RemoveMessage(BMessage *an_event);
		BMessage	*FindMessage(long index) const;
		BMessage	*FindMessage(ulong what, long index = 0) const;
		long		CountMessages() const;
		bool		IsEmpty() const;

		bool		Lock();
		void		Unlock();

// ------------------------------------------------------------------

private:
		char		message_filter(BMessage *an_event);
		BMessage	*FindMessage(bool anyWhat, ulong what, long index) const;

		BMessage	*the_queue;
		BMessage	*tail;
		long		message_count;
		char		debug;
		long		event_mask;
		long		system_mask;
		BLocker		locker;
};

#endif
