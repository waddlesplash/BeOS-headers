//******************************************************************************
//
//	File:		Messenger.h
//
//	Description:	Client application connect class.
//
//	Copyright 1992-94, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_MESSENGER_H
#define	_MESSENGER_H

#ifndef _INTERFACE_DEFS_H
#include <interface/InterfaceDefs.h>
#endif

#ifndef _RECT_H
#include <interface/Rect.h>
#endif

#ifndef _POINT_H
#include <interface/Point.h>
#endif

#ifndef _OS_H
#include <os/OS.h>
#endif

#ifndef _OBJECT_H
#include <support/Object.h>
#endif

#ifndef _WINDOW_H
#include <interface/Window.h>
#endif

#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif


//------------------------------------------------------------------------------

class BMessenger : public BObject {
	DECLARE_CLASS_INFO(BObject);

public:	
				BMessenger(const char *app_name);
				BMessenger(thread_id app_pid);
virtual			~BMessenger();

		void	SendMessage(BMessage *a_message, BMessage **reply);
		void	SendMessage(BMessage *a_message);
		long	Error();

// ------------------------------------------------------------------

private:
		thread_id	target_pid;
		long		fError;
};

//------------------------------------------------------------------------------

#endif
