//******************************************************************************
//
//	File:		Messenger.h
//
//	Description:	
//
//	Copyright 1992-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************


#ifndef	_MESSENGER_H
#define	_MESSENGER_H

#include <OS.h>
#include <Message.h>
#include <Handler.h>
#include <ClassInfo.h>

//------------------------------------------------------------------------------

class	BMessage;
class	BLooper;
class	BHandler;
class	_TRoster_;

class BMessenger {

public:	
					BMessenger();

					BMessenger(const char *mime_sig,
								team_id team = -1,
								status_t *perr = NULL);

					BMessenger(	const BHandler *handler,
								const BLooper *looper = NULL,
								status_t *perr = NULL);
					BMessenger(const BMessenger &from);
					~BMessenger();

		bool		IsTargetLocal() const;
		BHandler	*Target(BLooper **looper) const;
		bool		LockTarget() const;
		status_t	LockTargetWithTimeout(bigtime_t timeout) const;

		status_t	SendMessage(uint32 command, BHandler *reply_to = NULL) const;
		status_t	SendMessage(BMessage *a_message,
								BHandler *reply_to = NULL,
								bigtime_t timeout = B_INFINITE_TIMEOUT) const;
	
		status_t	SendMessage(uint32 command, BMessage *reply) const;
		status_t	SendMessage(BMessage *a_message,
								BMessage *reply,
								bigtime_t send_timeout = B_INFINITE_TIMEOUT,
								bigtime_t reply_timeout = B_INFINITE_TIMEOUT) const;
	
		BMessenger	&operator=(const BMessenger &from);
		bool		operator==(const BMessenger &other) const;

		bool		IsValid() const;
		team_id		Team() const;

// ------------------------------------------------------------------

private:
friend class BRoster;
friend class _TRoster_;
friend class BMessage;
friend inline void		_set_message_reply_(BMessage *, BMessenger);
				
					BMessenger(team_id team,
								port_id port,
								int32 token,
								bool preferred);

		void		InitData(const char *mime_sig,
							team_id team,
							status_t *perr);

		port_id		fPort;
		int32		fHandlerToken;
		team_id		fTeam;
		int32		extra0;
		int32		extra1;
		bool		fPreferredTarget;
		bool		extra2;
		bool		extra3;
		bool		extra4;
};

//------------------------------------------------------------------------------

#endif
