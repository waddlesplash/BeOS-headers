//******************************************************************************
//
//	File:		MessageQueue.h
//
//	Description:	MessageQueue object.
//
//	Copyright 1993-94, Be Incorporated
//
//******************************************************************************

#ifndef	_MESSAGE_QUEUE_H
#define	_MESSAGE_QUEUE_H

#ifndef _MESSAGE_H
#include <app/Message.h>
#endif
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class	BMessageQueue : BObject {
	DECLARE_CLASS_INFO(BObject);

public:
					BMessageQueue();	
virtual				~BMessageQueue();

		void		AddMessage(BMessage *an_event);
		BMessage	*NextMessage();
		void		RemoveMessage(ulong what);
		void		RemoveMessage(BMessage *an_event);
		BMessage	*FindMessage(ulong what, long index) const;
		long		CountMessages() const;
		bool		IsEmpty() const;

// ------------------------------------------------------------------

private:
		char		message_filter(BMessage *an_event);
		void		lock();
		void		unlock();

		BMessage	*the_queue;
		BMessage	*tail;
		long		message_count;
		char		debug;
		long		event_mask;
		long		system_mask;
		long		event_sem;
};

#endif
