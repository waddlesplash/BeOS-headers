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
		team_id		TeamFor(ulong signature) const;
		team_id		TeamFor(record_ref ref) const;
		void		GetAppList(BList *team_id_list) const;
		void		GetAppList(ulong signature, BList *team_id_list) const;
		long		GetAppInfo(ulong signature, app_info *info) const;
		long		GetAppInfo(record_ref ref, app_info *info) const;
		long		GetRunningAppInfo(team_id team, app_info *info) const;
		long		GetActiveAppInfo(app_info *info) const;
		long		Launch(	ulong signature,
							BMessage *initial_message = NULL,
							team_id *app_team = NULL);
		long		Launch(	ulong signature,
							BList *message_list,
							team_id *app_team = NULL);
		long		Launch(	ulong signature,
							long argc,
							char **args,
							team_id *app_team = NULL);
		long		Launch(	record_ref ref,
							BMessage *initial_message = NULL,
							team_id *app_team = NULL);
		long		Launch(	record_ref ref,
							BList *message_list,
							team_id *app_team = NULL);
		long		Launch(	record_ref ref,
							long argc,
							char **args,
							team_id *app_team = NULL);
		void		RemoveApp(team_id team);

//------------------------------------------------------------------------------
private:

friend class BApplication;
friend class BWindow;
friend class _BAppInit_;
friend int	_init_roster_();

		void		*operator new(size_t size);
		void		operator delete(void *p, size_t size);

					BRoster();
					~BRoster();
		
		ulong		AddApplication(	ulong signature,
									record_ref ref,
									ulong flags,
									team_id team,
									port_id port,
									bool full_reg);
		void		SetSignature(thread_id thread, ulong signature);
		void		SetThread(team_id team, thread_id tid);
		void		SetThreadAndTeam(ulong entry_token,
									 thread_id tid,
									 team_id team);
		void		CompleteRegistration(team_id team, port_id port);
		bool		IsAppPreRegistered(	record_ref ref,
										team_id team,
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
										team_id *app_team);
		long		FindRecord(	ulong signature,
								record_ref ref,
								BRecord **rec) const;
		void		NotifyBrowser(	ulong signature,
									team_id team,
									ulong flags,
									record_ref ref);
		bool		UpdateActiveApp(team_id team);
		void		SetAppFlags(team_id team, ulong flags);

		BLocker		fLock;
		long		fCount;
		_p_ainfo_	*fData;
		long		fPhysicalCount;
		ulong		fListeners[50];
		BMessenger	*fBrowser;
		ulong		fEntryToken;
		team_id		fActiveApp;
};

extern BRoster *be_roster;

#endif
