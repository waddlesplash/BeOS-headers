//******************************************************************************
//
//	File:		Application.h
//
//	Description:	Client application class.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1992-93, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_APPLICATION_H
#define	_APPLICATION_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef _RECT_H
#include "Rect.h"
#endif
#ifndef _POINT_H
#include "Point.h"
#endif
#ifndef	_EVENT_H
#include "Event.h"
#endif
#ifndef _OBJECT_H
#include <sys/Object.h>
#endif

class BView;

class BRect;
class BList;
class BSession;
class BWindow;
class BParcel;
typedef long ResHandle;
typedef BView *(view_creation_func)(BRect *frame, char *name,
		ulong resizeMask, ulong flags, void *resData, long baseType);
//------------------------------------------------------------------------------

typedef struct {
		long param1;
		long param2;
		long param3;
		long param4;
		long param5;
		long param6;
		long param7;
		long param8;
	} app_message;

//------------------------------------------------------------------------------

class BApplication : public BObject {

public:
			BApplication();
virtual			~BApplication();
virtual	char		*ClassName();

	void		Run();
	void		Quit();
virtual	void		Tick();

	void		Lock();
	void		Unlock();
	void		SetCursor(void* cursor, long size);
	BWindow		*FindWindow(BPoint);
	BWindow		*GetWindow(long index);
	void		CloseAllWindows();
	long		CountWindows();
virtual	void		MessageReceived(long sender, long msg, 
					app_message *msgBuffer = NIL);
	bool		SendMessage(const char *to, long msg, 
				    app_message *msgBuffer = NIL);
	bool		SendMessage(long to, long msg, 
				    app_message *msgBuffer = NIL);
	void		WaitForReply(long* sender, long* msg, 
		       	            app_message *msgBuffer = NIL);
	uchar		IndexForColor(rgb_color c);
	uchar		IndexForColor(uchar r, uchar g, uchar b, uchar a = 0);		
	color_map 	*ColorMap();	
	long		IdleTime();
	BEvent		*CurrentEvent();
	long		CountScreens();
	void		GetScreenInfo(screen_info *, long index = 0);
	void		GetServerVersion(char *);
	void		GetKitVersion(char *);
	void		RegisterView(const char *className, view_creation_func);
virtual	void		DispatchEvent(BEvent *an_event);
virtual	void		CommandReceived(BCommandEvent *an_event);
	void		PostEvent(BEvent *an_event);
	void		PostCommand(long command);


//------------------------------------------------------------------------------

friend class BImageBuffer;
friend BView *EditViewCreate(BRect *frame, char *name, ulong resizeMask, ulong flags, void *resData, long id);
friend class DlgWindow;
friend class ScrollSettings;
friend class RectSettings;
friend class BWindow;
friend class BBitmap;
friend class BView;
friend class BScrollBar;
//??? temp menu stuff
friend class TMenuBar;
friend class TMenu;
friend class PropWindow;
friend class WindowSettings;
friend class MainWindow;
friend class DlgWindow;
friend void _flush_task_();

private:

	void		queue_event(app_message *a_message);
	long		OpenResourceFile(char *name = (char *) 0);
	long		LoadResource(ulong type, ulong id, void **p, long *len);
	long		AddResource(ulong type, ulong id, void *buf, long len);
	long		DeleteResource(ulong type, ulong id);
	ResHandle	ResourceHandle(void) { return resources; };
	void		DeregisterView(const char *className);
	BView		*NewView(const char *className, const BRect *frame, const char *name, ulong resizeMask, ulong flags, void *resData, long baseType);
	void		BeginRectTracking(BRect *);
	void		EndRectTracking();
	void		add_to_window_list(BWindow *);
	void		remove_from_window_list(BWindow *);
	void		flush_task();
	void		get_scs();
	BSession	*session();
	void		send_drag(BParcel *a_brol, long vs_token, BRect drag_rect);
	void		send_drag(BParcel *a_brol, long vs_token, long dh, long dv, long bitmap_token);

	BWindow*	local_window_list;
	long		server_from;
	long		server_to;
	long		msg_task_id;
	long		flush_task_id;
	long		app_sem;
	BSession	*main_session;
	color_map	*system_cs;	// ## should be static?
	ResHandle	resources;
	BList		*viewList;
	view_creation_func *defaultCreate;
	bool		fQuitFlag;
	bool		fIgnoreBase;
	BEventQueue	*event_queue;
	BEvent		*last_event;	
};

inline char 		*BApplication::ClassName() { return "BApplication"; };
inline long		BApplication::CountScreens() { return(1); };

//------------------------------------------------------------------------------

extern BApplication *be_app;

//------------------------------------------------------------------------------

#endif
