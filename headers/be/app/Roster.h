//******************************************************************************
//
//	File:			Roster.h
//
//	Description:	Client BRoster class. Used to keep track of all running
//					applications in the system.
//
//	Copyright 1992-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef _ROSTER_H
#define _ROSTER_H

#ifndef _OBJECT_H
#include <Object.h>
#endif
#ifndef _OS_H
#include <OS.h>
#endif
#ifndef _MESSAGE_H
#include <Message.h>
#endif
#ifndef _STORAGE_DEFS_H
#include <StorageDefs.h>
#endif
#ifndef _LIST_H
#include <List.h>
#endif
#ifndef _LOCKER_H
#include <Locker.h>
#endif

class BApplication;
class BWindow;
class BMessenger;
struct _p_ainfo_;
extern "C" int	_init_roster_();

#define B_LAUNCH_MASK				(0x3)

#define B_SINGLE_LAUNCH				(0x0)
#define B_MULTIPLE_LAUNCH			(0x1)
#define B_EXCLUSIVE_LAUNCH			(0x2)

#define B_BACKGROUND_APP			(0x4)
#define B_ARGV_ONLY					(0x8)
#define _B_APP_INFO_RESERVED1_		(0x10000000)

struct app_info {
	ulong		signature;
	thread_id	thread;
	team_id		team;
	port_id		port;
	record_ref	ref;
	ulong		flags;
};

//------------------------------------------------------------------------------

class BRoster {
	
	// because BRoster is a shared object (across address spaces) it
	// can't have any virtual functions. Therefore it doesn't inherit from
	// BObject or participate in the Class Info system.

public:
		bool		IsRunning(ulong signature) const;
		bool		IsRunning(record_ref ref) const;
		thread_id	ThreadFor(ulong signature) const;
		thread_id	ThreadFor(record_ref ref) const;
		void		GetThreadList(BList *threads) const;
		void		GetThreadList(ulong signature, BList *threads) const;
		long		GetAppInfo(ulong signature, app_info *info) const;
		long		GetAppInfo(record_ref ref, app_info *info) const;
		long		GetRunningAppInfo(thread_id thread, app_info *info) const;
		long		GetActiveAppInfo(app_info *info) const;
		long		Launch(	ulong signature,
							BMessage *initial_message = NULL,
							thread_id *app_thread = NULL);
		long		Launch(	ulong signature,
							BList *message_list,
							thread_id *app_thread = NULL);
		long		Launch(	ulong signature,
							long argc,
							char **args,
							thread_id *app_thread = NULL);
		long		Launch(	record_ref ref,
							BMessage *initial_message = NULL,
							thread_id *app_thread = NULL);
		long		Launch(	record_ref ref,
							BList *message_list,
							thread_id *app_thread = NULL);
		long		Launch(	record_ref ref,
							long argc,
							char **args,
							thread_id *app_thread = NULL);
		void		RemoveApplication(thread_id thread);
		void		RemoveTeam(team_id team);

//------------------------------------------------------------------------------
private:

friend class BApplication;
friend class BWindow;
friend class _BAppInit_;
friend int	_init_roster_();

		void		Lock();
		void		Unlock();

		void		*operator new(size_t size);
		void		operator delete(void *p, size_t size);

					BRoster();
					~BRoster();
		
		ulong		AddApplication(	ulong signature,
									record_ref ref,
									ulong flags,
									thread_id thread,
									port_id port,
									bool full_reg);
		void		SetSignature(thread_id thread, ulong signature);
		void		SetThread(ulong entry_token, thread_id thread);
		thread_id	CompleteRegistration(thread_id thread, port_id port);
		bool		IsAppPreRegistered(	record_ref ref,
										thread_id thread,
										app_info *info) const;
		void		RemovePreRegApp(ulong signature, record_ref ref);
		long		IndexOfApp(ulong signature) const;
		long		IndexOfThread(thread_id thread) const;
		long		IndexOfTeam(team_id thread) const;
		long		IndexOfRef(record_ref) const;
		long		IndexOfPort(port_id port) const;
		long		IndexOfToken(ulong a_token) const;
		long		GetIndexInfo(long index, app_info *info) const;
		void		RemoveIndex(long index);
		long		LaunchAppPrivate(	ulong signature,
										record_ref ref,
										BList* msg_list,
										long cargs,
										char **args,
										thread_id *app_thread);
		long		FindRecord(	ulong signature,
								record_ref ref,
								BRecord **rec) const;
		void		NotifyBrowser(	ulong signature,
									thread_id thread,
									ulong flags,
									record_ref ref);
		bool		UpdateActiveApp(thread_id thread);
		void		SetAppFlags(thread_id thread, ulong flags);

		BLocker		fLock;
		long		fCount;
		_p_ainfo_	*fData;
		long		fPhysicalCount;
		ulong		fListeners[50];
		BMessenger	*fBrowser;
		ulong		fEntryToken;
		thread_id	fActiveApp;
};

extern BRoster *be_roster;

#endif
