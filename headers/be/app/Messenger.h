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
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif
#ifndef _MESSAGE_H
#include "Message.h"
#endif

//------------------------------------------------------------------------------

class BMessenger : public BObject {
	B_DECLARE_CLASS_INFO(BObject);

public:	
		void	*operator new(size_t size);

				BMessenger(ulong signature, thread_id thread = -1);
virtual			~BMessenger();

		long	SendMessage(ulong command, BMessage **reply);
		long	SendMessage(ulong command);
		long	SendMessage(BMessage *a_message, BMessage **reply);
		long	SendMessage(BMessage *a_message);
		long	Error();

// ------------------------------------------------------------------

private:
friend class BRoster;
				
				BMessenger(port_id port, int, int);

		void	*operator new(size_t size, void *buffer);

		port_id		fPort;
		long		fError;
};

//------------------------------------------------------------------------------

#endif
