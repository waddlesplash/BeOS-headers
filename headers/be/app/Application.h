//******************************************************************************
//
//	File:		Application.h
//
//	Description:	Client application class.
//
//	Copyright 1992-94, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_APPLICATION_H
#define	_APPLICATION_H

#ifndef _INTERFACE_DEFS_H
#include <interface/InterfaceDefs.h>
#endif

#ifndef _RECT_H
#include <interface/Rect.h>
#endif

#ifndef _POINT_H
#include <interface/Point.h>
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

#ifndef _MESSENGER_H
#include "Messenger.h"
#endif

class BView;

class BRect;
class BList;
class _BSession;
class BWindow;
typedef long ResHandle;
typedef BView *(view_creation_func)(BRect frame, const char *name,
		ulong resizeMask, ulong flags, void *resData, long baseType);
//------------------------------------------------------------------------------

class BApplication : public BObject {
	DECLARE_CLASS_INFO(BObject);

public:
						BApplication();
virtual					~BApplication();

		BMessage*		RunFileService();
		BMessage*		RunFileService(char* saveName);

virtual	void			Pulse();
virtual	void			ReadyToRun();
virtual	void			Activate();

		void			Run(char* name);

virtual bool			QuitRequested();
		void			Quit();
	
		bool			Lock();
		void			Unlock();
		BMessageQueue	*MessageQueue();
		void			ShowCursor();
		void			HideCursor();
		void			ObscureCursor();
		void			SetCursor(void* cursor, long size);
		BWindow			*FindWindow(BPoint) const;
		BWindow			*WindowAt(long index) const;
		bool			CloseAllWindows(bool makeRequest);
		long			CountWindows() const;
/*virtual	void			WindowClosed();*/
		long			IdleTime() const;
		void			GetServerVersion(char *) const;
		void			GetKitVersion(char *) const;
		void			RegisterView(const char *className, view_creation_func);
virtual	void			DispatchMessage(BMessage *an_event);
virtual	void			MessageReceived(BMessage *a_message);
		void			PostMessage(BMessage *a_message);
		void			PostMessage(ulong command);
		void			SetPulseRate(long rate);
		BMessage 		*CurrentMessage() const;
		BMessage		*DetachCurrentMessage();
	
		ResHandle		ResourceHandle(void) const;
		void			SetResourceHandle(ResHandle newres);
		thread_id		MainThread();

// ------------------------------------------------------------------

private:

friend class BImageBuffer;
friend BView *EditViewCreate(	BRect frame,
								char *name,
								ulong resizeMask,
								ulong flags,
								void *resData,
								long id);

friend class BWindow;
friend class BBitmap;
friend class BView;
friend class BScrollBar;
friend void _flush_task_();
friend _BSession *app_session();

		void			run_task();
		long			OpenResourceFile(char *name = (char *) 0);
		long			LoadResource(ulong type, ulong id, void **p, long *len);
		long			AddResource(ulong type, ulong id, void *buf, long len);
		long			DeleteResource(ulong type, ulong id);
		void			DeregisterView(const char *className);
		BView			*NewView(	const char *className,
									BRect frame,
									const char *name,
									ulong resizeMask,
									ulong flags,
									void *resData,
									long baseType);
		void			BeginRectTracking(BRect r, bool trackWhole);
		void			EndRectTracking();
		void			add_to_window_list(BWindow *);
		void			remove_from_window_list(BWindow *);
		void			flush_task();
		void			get_scs();
		void			get_key_trans_maps();
		_BSession		*session();
		void			send_drag(	BMessage *a_brol,
									long vs_token,
									BRect drag_rect);
		void			send_drag(	BMessage *a_brol,
									long vs_token,
									long dh,
									long dv,
									long bitmap_token);
		void			write_drag(_BSession *the_session, BMessage *a_message);
		void			do_quit();
		bool			close_all_windows(bool makeRequest, bool quitting);

		BMessageQueue	*message_queue;
		BMessage		*last_message;
		long			token;
		long			main_task_id;
		BWindow*		local_window_list;
		long			server_from;
		long			server_to;
		long			flush_task_id;
		long			lock_sem;
		long			lock_owner_count;
		long			lock_owner;
		_BSession		*main_session;
		ResHandle		resources;
		BList			*viewList;
		bool			fIgnoreBase;
		long			pulse_rate;
		long			pulse_phase;
		view_creation_func	*defaultCreate;
		BMessage		*fBrowserMessage;
};

inline ResHandle BApplication::ResourceHandle(void) const
	{ return resources; }

inline void BApplication::SetResourceHandle(ResHandle newres)
	{ resources = newres; }


//------------------------------------------------------------------------------

extern BApplication *be_app;

//------------------------------------------------------------------------------

#endif
