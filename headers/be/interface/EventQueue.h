//******************************************************************************
//
//	File:		EventQueue.h
//
//	Description:	EventQueue object.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1993, Be Incorporated
//
//******************************************************************************

#ifndef	_EVENT_QUEUE_H
#define	_EVENT_QUEUE_H

#ifndef _EVENT_H
#include "Event.h"
#endif

//------------------------------------------------------------------------------

class	BEventQueue : BObject {
public:
			BEventQueue();	
virtual			~BEventQueue();
	void		AddEvent(BEvent *an_event);
	BEvent		*NextEvent();
	void		RemoveType(long context, long what);
	void		RemoveEvent(BEvent *an_event);
	BEvent		*FindEvent(long context, long what, long index);
	long		CountEvents();
	bool		IsEmpty();

private:
	char		event_filter(BEvent *an_event);
	void		lock();
	void		unlock();

	BEvent		*the_queue;
	BEvent		*tail;
	long		event_count;
	char		debug;
	long		event_mask;
	long		system_mask;
	long		event_sem;
};

#endif
