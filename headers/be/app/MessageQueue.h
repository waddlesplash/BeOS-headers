//******************************************************************************
//
//	File:		MessageQueue.h
//
//	Description:	MessageQueue object.
//
//	Copyright 1993-97, Be Incorporated
//
//******************************************************************************


#ifndef	_MESSAGE_QUEUE_H
#define	_MESSAGE_QUEUE_H

#include <Message.h>
#include <Locker.h>

//------------------------------------------------------------------------------

class	BMessageQueue {

public:
					BMessageQueue();	
virtual				~BMessageQueue();

		void		AddMessage(BMessage *an_event);
		BMessage	*NextMessage();
		bool		RemoveMessage(BMessage *an_event);
		BMessage	*FindMessage(int32 index) const;
		BMessage	*FindMessage(uint32 what, int32 index = 0) const;
		int32		CountMessages() const;
		bool		IsEmpty() const;

		bool		Lock();
		void		Unlock();

// ------------------------------------------------------------------

private:

virtual	void		_ReservedMessageQueue1();
virtual	void		_ReservedMessageQueue2();
virtual	void		_ReservedMessageQueue3();

					BMessageQueue(const BMessageQueue &);
		BMessageQueue &operator=(const BMessageQueue &);

		char		message_filter(BMessage *an_event);
		BMessage	*FindMessage(bool anyWhat, uint32 what, int32 index) const;

		BMessage	*the_queue;
		BMessage	*tail;
		int32		message_count;
		BLocker		locker;
		uint32		_reserved[3];
};

#endif
