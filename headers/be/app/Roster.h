/*****************************************************************************
//
//	File:			Roster.h
//
//	Description:	Client BRoster class. Used to keep track of all running
//					applications in the system.
//
//	Copyright 1992-97, Be Incorporated, All Rights Reserved.
//
******************************************************************************/

#ifndef _ROSTER_H
#define _ROSTER_H

#include <OS.h>
#include <Message.h>
#include <StorageDefs.h>
#include <List.h>
#include <Locker.h>
#include <Mime.h>

class BApplication;
class BWindow;
class BMessenger;
class BResourceFile;
class BNodeInfo;

extern "C" int	_init_roster_();

#define B_LAUNCH_MASK				(0x3)

#define B_SINGLE_LAUNCH				(0x0)
#define B_MULTIPLE_LAUNCH			(0x1)
#define B_EXCLUSIVE_LAUNCH			(0x2)

#define B_BACKGROUND_APP			(0x4)
#define B_ARGV_ONLY					(0x8)
#define _B_APP_INFO_RESERVED1_		(0x10000000)

struct app_info {
				app_info();
				~app_info();

	thread_id	thread;
	team_id		team;
	port_id		port;
	uint32		flags;
	entry_ref	ref;
	char		signature[B_MIME_TYPE_LENGTH];
};

//------------------------------------------------------------------------------

class BRoster {
public:
					BRoster();
					~BRoster();
		
		bool		IsRunning(const char *mime_sig) const;
		bool		IsRunning(entry_ref *ref) const;
		team_id		TeamFor(const char *mime_sig) const;
		team_id		TeamFor(entry_ref *ref) const;
		void		GetAppList(BList *team_id_list) const;
		void		GetAppList(const char *sig, BList *team_id_list) const;
		status_t	GetAppInfo(const char *sig, app_info *info) const;
		status_t	GetAppInfo(entry_ref *ref, app_info *info) const;
		status_t	GetRunningAppInfo(team_id team, app_info *info) const;
		status_t	GetActiveAppInfo(app_info *info) const;
		status_t	ActivateApp(team_id team) const;
		status_t	Broadcast(BMessage *msg) const;

		status_t	Launch(	const char *mime_type,
							BMessage *initial_msgs = NULL,
							team_id *app_team = NULL) const;
		status_t	Launch(	const char *mime_type,
							BList *message_list,
							team_id *app_team = NULL) const;
		status_t	Launch(	const char *mime_type,
							int argc,
							char **args,
							team_id *app_team = NULL) const;

		status_t	Launch(	entry_ref *ref,
							BMessage *initial_message = NULL,
							team_id *app_team = NULL) const;
		status_t	Launch(	entry_ref *ref,
							BList *message_list,
							team_id *app_team = NULL) const;
		status_t	Launch(	entry_ref *ref,
							int argc,
							char **args,
							team_id *app_team = NULL) const;

		status_t	FindApp(const char *mime_type, entry_ref *app) const;
		status_t	FindApp(entry_ref *ref, entry_ref *app) const;

//------------------------------------------------------------------------------
private:

friend class BApplication;
friend class BWindow;
friend class _BAppCleanup_;
friend int	_init_roster_();
friend status_t _send_to_roster_(BMessage *, BMessage *, bool);
friend bool _is_valid_roster_mess_(bool);

		uint32		AddApplication(	const char *mime_sig,
									entry_ref *ref,
									uint32 flags,
									team_id team,
									thread_id thread,
									port_id port,
									bool full_reg) const;
		void		SetSignature(team_id team, const char *mime_sig) const;
		void		SetThread(team_id team, thread_id tid) const;
		void		SetThreadAndTeam(uint32 entry_token,
									 thread_id tid,
									 team_id team) const;
		void		CompleteRegistration(team_id team,
										thread_id,
										port_id port) const;
		bool		IsAppPreRegistered(	entry_ref *ref,
										team_id team,
										app_info *info) const;
		void		RemovePreRegApp(uint32 entry_token) const;
		void		RemoveApp(team_id team) const;

		status_t	xLaunchAppPrivate(	const char *mime_sig,
										entry_ref *ref,
										BList* msg_list,
										int cargs,
										char **args,
										team_id *app_team) const;
		bool		UpdateActiveApp(team_id team) const;
		void		SetAppFlags(team_id team, uint32 flags) const;
		void		DumpRoster() const;
		status_t	resolve_app(const char *in_type,
								const entry_ref *ref,
								entry_ref *app_ref,
								char *app_sig,
								uint32 *app_flags,
								bool *was_document) const;
		status_t	translate_ref(const entry_ref *ref,
								BMimeType *app_meta,
								entry_ref *app_ref,
								BFile *app_file,
								char *app_sig,
								bool *was_document) const;
		status_t	translate_type(const char *mime_type,
								BMimeType *meta,
								entry_ref *app_ref,
								BFile *app_file,
								char *app_sig) const;
		status_t	sniff_file(const entry_ref *file,
								BNodeInfo *finfo,
								char *mime_type) const;
		status_t	query_for_app(BMimeType *meta, entry_ref *app_ref) const;
		status_t	get_unique_supporting_app(const BMessage *apps,
											char *out_sig) const;
		char		**build_arg_vector(char **args, int *pargs,
										const entry_ref *app_ref,
										const entry_ref *doc_ref) const;
		status_t	send_to_running(team_id tema,
									const entry_ref *app_ref,
									int cargs, char **args,
									const BList *msg_list,
									const entry_ref *ref) const;
		void		InitMessengers();

		BMessenger	fMess;
		BMessenger	fMimeMess;
		uint32		_fReserved[3];
};

extern const BRoster *be_roster;

#endif
