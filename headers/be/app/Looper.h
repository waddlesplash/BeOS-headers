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
#ifndef _LIST_H
#include <List.h>
#endif
#ifndef _HANDLER_H
#include <Handler.h>
#endif
#ifndef _MESSAGE_H
#include <Message.h>
#endif

class BHandler;
class BMessageQueue;
class BMessenger;
class BList;
struct _loop_data_;

class BLooper : public BHandler {

public:
						BLooper(const char *name = NULL,
								long priority = B_NORMAL_PRIORITY);
virtual					~BLooper();

		bool			Lock();
		void			Unlock();
		thread_id		LockOwner() const;
		bool			IsLocked() const;

		long			PostMessage(BMessage *message,
									BHandler *handler = NULL);
		long			PostMessage(ulong command,
									BHandler *handler = NULL);
virtual	void			DispatchMessage(BMessage *message, BHandler *handler);
		BMessage		*CurrentMessage() const;
		BMessage		*DetachCurrentMessage();

		BMessageQueue	*MessageQueue() const;

		thread_id		Thread() const;
		team_id			Team() const;

virtual	void			AddHandler(BHandler *handler);
virtual	bool			RemoveHandler(BHandler *handler);
virtual	BHandler		*PreferredHandler() const;

virtual	thread_id		Run();
virtual	void			Quit();
virtual	bool			QuitRequested();
virtual	void			HandlersRequested(BMessage *msg);
		
virtual	void		AddCommonFilter(BMessageFilter *filter);
virtual	bool		RemoveCommonFilter(BMessageFilter *filter);
virtual	void		SetCommonFilterList(BList *filters);
		BList		*CommonFilterList();

private:
friend class BWindow;
friend class BApplication;
friend class BMessenger;
friend class BView;

friend inline port_id _get_handler_port_(const BHandler *);

						// private constructor for BApplication
						BLooper(const char *name, long priority, port_id port);

		void			InitData();
		void			AddMessage(BMessage *msg);
static	long			_task0_(void *arg);
virtual	void			task_looper();
		void			do_quit_requested();
		bool			AssertLocked() const;
		BHandler		*filter_message(BMessage *msg, BHandler *target);
		BHandler		*apply_filters(	BList *list,
										BMessage *msg,
										BHandler *target);

static	ulong			sLooperID;
static	long			sLooperListSize;
static	long			sLooperCount;
static	_loop_data_		*sLooperList;
static	BLocker			sLooperListLock;

static	void			AddLooper(BLooper *l);
static	bool			IsLooperValid(BLooper *l);
static	void			RemoveLooper(BLooper *l);
static	void			GetLooperList(BList *list);
static	BLooper			*FindLooper(const char *name);
		
		long			fLooperID;
		BMessageQueue	*fQueue;
		BMessage		*fLastMessage;
		port_id			fMsgPort;
		long			fAtomicCount;
		sem_id			fLockSem;
		long			fOwnerCount;
		thread_id		fOwner;
		thread_id		fTaskID;
		team_id			fTeamID;
		sem_id			fCloseSem;
		long			fInitPriority;
		BList			fHandlers;
		BList			*fCommonFilters;
		bool			fTerminating;
		bool			fRunCalled;
		bool			fWasFiltered;
		//long			cached_pid;
		//long			cached_stack;
};

inline thread_id BLooper::LockOwner() const
	{ return fOwner; }

inline bool BLooper::IsLocked() const
	{ return (fOwner == find_thread(NULL)); }

#endif
