//******************************************************************************
//
//	File:		Window.h
//
//	Description:	Client window class.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1992-93, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_WINDOW_H
#define	_WINDOW_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef	_PARCEL_H
#include "Parcel.h"
#endif
#ifndef _RECT_H
#include "Rect.h"
#endif
#ifndef _VIEW_H
#include "View.h"
#endif
#ifndef	_EVENT_QUEUE_H
#include "EventQueue.h"
#endif
#ifndef	_OBJECT_H
#include <sys/Object.h>
#endif

//------------------------------------------------------------------------------

typedef enum { SHADOWED_WINDOW,
       	       TITLED_WINDOW,
       	       BORDERED_WINDOW,
       	       MODAL_WINDOW,
       	       BACKDROP_WINDOW,
       	       QUERY_WINDOW } window_type;

/*----------------------------------------------------------------*/
/* window manager flags for windows properties			  */
/*----------------------------------------------------------------*/

const long NOT_MOVABLE = 0x00000001;
const long NOT_H_RESIZABLE = 0x00000004;
const long NOT_V_RESIZABLE = 0x00000008;
const long NOT_RESIZABLE = 0x00000002;
const long ACCEPTS_FIRST_CLICK = 0x00000010;
const long NOT_CLOSABLE = 0x00000020;
const long NOT_ZOOMABLE = 0x00000040;
const long FLOATING = 0x00000080;

/*----------------------------------------------------------------*/

struct message;
class BSession;
class BList;

class BWindow : public BObject {

public:
			BWindow(const BRect *frame, char *title, 
				window_type type, ulong flags);
			BWindow();
virtual	void		Close();
virtual			~BWindow();
virtual	char		*ClassName();
	
	long		Token();

virtual	bool		FilterKeyDown(ulong *aKey);	
virtual	bool		FilterMouseDown(BPoint*, BView *targetView);
virtual	bool		FilterParcelDropped(BPoint *, BParcel *);
virtual	bool		FilterMouseMoved(BPoint *, ulong code, bool has_parcel);
	void		AddChild(BView *);
	void		RemoveChild(BView *);
virtual	void		DispatchEvent(BEvent *);
virtual	void		CommandReceived(BCommandEvent *);
virtual	void		FrameMoved(BPoint new_position);
virtual	void		FrameResized(long new_width, long new_height);		
virtual	void		CloseRequested();	
	void		PostEvent(BEvent *);
	void		PostEvent(BEvent *, BView *);
	void		PostEvent(BEvent *, char *view_name);
	void		PostCommand(long command);
	void		PostCommand(long command, BView *);
	void		PostCommand(long command, char *view_name);
	BEvent		*CurrentEvent();
	bool		LoadFromResource(long resID);
	void		AddKeyCommand(ulong key, ulong modifiers, long cmd);
	void		RemoveKeyCommand(ulong key, ulong modifiers);
	ulong		ModifierKeys();
	void		UpdateIfNeeded();
	BView		*FindView(char *view_name);
	BView		*FindView(BPoint);
	BView		*FocusView();
	void		Lock();
	void		Unlock();
	void		Activate(bool = TRUE);
virtual	void		WindowActivated(bool state);
	void		ConvertToScreen(BPoint* );
	void		ConvertFromScreen(BPoint* );
	void		ConvertToScreen(BRect *);
	void		ConvertFromScreen(BRect *);
	void		MoveBy(long dx, long dy);
	void		MoveTo(BPoint);
	void		MoveTo(long x, long y);
	void		ResizeBy(long dx, long dy);
	void		ResizeTo(long width, long height);
	void		Show();
	void		Hide();
	bool		IsHidden();
	void		GetBounds(BRect *);
	void		GetFrame(BRect *);
	void		GetTitle(char *);
	void		SetTitle(char *);
	bool		IsFront();
	bool		IsActive();
	BEventQueue	*EventQueue();
	void		RemoveMouseEvents();
//------------------------------------------------------------------------------

friend class BApplication;
friend class PropWindow;
friend class WindowSettings;
friend class BImageBuffer;
friend class BScrollBar;
friend class BView;
//??? temp menu stuff
friend class TMenuBar;
friend class TMenu;
friend void _task0_();
friend class EditView;
friend class DlgWindow;
friend class MainWindow;
friend BView *EditViewCreate(BRect *frame, char *name, ulong resizeMask, 
			     ulong flags, void *resData, long id);


private:
	BWindow		*next_window;
	BEventQueue	*event_queue;
	BEvent		*last_event;	
	long		server_token;
	long		client_token;
	char		update_buzy;
	char		f_active;
	short		fShowLevel;

	long		send_port;
	long		receive_port;
	long		inter_port;
	long		task_id;
	long		lock_sem;
	long		lock_owner_count;
	long		lock_owner;

	BView		*top_view;
	BView		*focus;
	BView		*last_mm_target;
	BSession	*a_session;
	BParcel		*last_tbrol;
	BList		*accelList;
	long		last_vs_token;
	long		drag_bitmap_token;
	BRect		last_drag_rect;
	long		drag_dh;
	long		drag_dv;
	long		id;
	long		top_view_token;

	long		GetID(void) { return id; };
	void		SetID(long newID) { id = newID; };
	bool		SaveAsResource(long resID);

	void		Flush();
	void		close1();
	void		task();
	void		set_brol(BParcel *, long vs_token, BRect track_rect);
	void		set_brol(BParcel *, long vs_token, long dh, long dv, long bitmap_token);
	void		set_brol(BParcel *);
	void		force_drag();
	void		view_builder(BView *a_view);
	long		get_server_token();
	void		do_drop(BSysEvent *an_event);
	void		movesize(long opcode, long h, long v);
	void		do_gen_event(message *a_message);
	
	void		handle_activate(BSysEvent *an_event);
	void		do_view_frame(BSysEvent *an_event);
	void		do_value_change(BSysEvent *an_event);
	void		do_mouse_down(BSysEvent *an_event);
	void		do_mouse_moved(BSysEvent *an_event);
	void		do_key_down(BSysEvent *an_event);
	void		do_draw_view(message *a_message);
	void		queue_event(message *a_message);
	void		dequeue_as_much_as_possible();
};

inline char		*BWindow::ClassName() { return "BWindow"; };
inline long		BWindow::Token() { return server_token; };

#endif
