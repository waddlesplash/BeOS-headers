//******************************************************************************
//
//	File:		Messenger.h
//
//	Description:	Client application connect class.
//
//	Copyright 1992-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_MESSENGER_H
#define	_MESSENGER_H

#ifndef _OS_H
#include <OS.h>
#endif
#ifndef _OBJECT_H
#include <Object.h>
#endif
#ifndef _MESSAGE_H
#include <Message.h>
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class	BHandler;
class	BMessage;

// This class shouldn't have a vtable

class BMessenger {

public:	
		void	*operator new(size_t size);

				BMessenger();
				BMessenger(ulong signature, team_id team = -1);
				BMessenger(const BHandler *handler);
				BMessenger(const BMessenger &from);
				~BMessenger();

		long	SendMessage(ulong command, BHandler *reply_to = NULL);
		long	SendMessage(BMessage *a_message, BHandler *reply_to = NULL);

		long	SendMessage(ulong command, BMessage **reply);
		long	SendMessage(BMessage *a_message, BMessage **reply);

		long	Error();

		BMessenger	FindHandler(BMessage *find_msg);
		BMessenger	FindHandler(long index, const char *the_class = NULL);
		BMessenger	FindHandler(const char *name, const char *the_class =NULL);
		BMessage	*FindAllHandlers(const char *the_class = NULL);

		BMessenger	&operator=(const BMessenger &from);

// ------------------------------------------------------------------

private:
friend class BRoster;
friend class BMessage;
				
		void	*operator new(size_t size, void *buffer);

		port_id		fPort;
		long		fHandlerToken;
		team_id		fTeam;
		long		fError;
};

//------------------------------------------------------------------------------

#endif
