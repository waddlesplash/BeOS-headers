//******************************************************************************
//
//	File:			Looper.h
//
//	Description:	Client looper class.
//
//	Copyright 1995-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef _LOOPER_H
#define _LOOPER_H

#ifndef _OS_H
#include <OS.h>
#endif
#ifndef _RECEIVER_H
#include <Receiver.h>
#endif
#ifndef _MESSAGE_H
#include <Message.h>
#endif

class BReceiver;
class BMessageQueue;
class BList;
struct _loop_data_;

class BLooper : public BReceiver {
	B_DECLARE_CLASS_INFO(BReceiver);

public:
						BLooper(long priority = B_DISPLAY_PRIORITY);
virtual					~BLooper();

		bool			Lock();
		void			Unlock();
		thread_id		LockOwner();

virtual	long			PostMessage(BMessage *message,
									BReceiver *receiver = NULL);
		long			PostMessage(ulong command,
									BReceiver *receiver = NULL);
virtual	void			DispatchMessage(BMessage *message, BReceiver *receiver);
		BMessage		*CurrentMessage() const;
		BMessage		*DetachCurrentMessage();

		BMessageQueue	*MessageQueue() const;

		thread_id		Thread() const;

virtual	BLooper			*Looper() const;
virtual	BReceiver		*PreferredReceiver() const;

virtual	thread_id		Run();
virtual	void			Quit();
virtual	bool			QuitRequested();
		
private:
friend class BWindow;
friend class BApplication;

						// private constructor for BApplication
						BLooper(long priority, port_id port);

		void			InitData();
		void			AddMessage(BMessage *msg);
static	long			_task0_(void *arg);
virtual	void			task_looper();
		void			do_quit_requested();

static	ulong			sLooperID;
static	long			sLooperListSize;
static	long			sLooperCount;
static	_loop_data_		*sLooperList;
static	BLocker			sLooperListLock;

static	void			AddLooper(BLooper *l);
static	bool			IsLooperValid(BLooper *l);
static	void			RemoveLooper(BLooper *l);
static	void			GetLooperList(BList *list);
		
		long			fLooperIndex;
		long			fLooperID;
		BMessageQueue	*fQueue;
		BMessage		*fLastMessage;
		port_id			fMsgPort;
		sem_id			fLockSem;
		long			fOwnerCount;
		thread_id		fOwner;
		thread_id		fTaskID;
		bool			fTerminating;
		bool			fRunCalled;
		sem_id			fCloseSem;
		long			fInitPriority;
};

inline thread_id BLooper::LockOwner()
	{ return fOwner; }

#endif
