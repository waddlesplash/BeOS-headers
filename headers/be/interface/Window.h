//******************************************************************************
//
//	File:		Window.h
//
//	Description:	Client window class.
//
//	Copyright 1992-94, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_WINDOW_H
#define	_WINDOW_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef _RECT_H
#include "Rect.h"
#endif
#ifndef _VIEW_H
#include "View.h"
#endif
#ifndef	_MESSAGE_QUEUE_H
#include <app/MessageQueue.h>
#endif
#ifndef	_OBJECT_H
#include <support/Object.h>
#endif
#ifndef _MESSAGE_H
#include <app/Message.h>
#endif
#ifndef _LIST_H
#include <support/List.h>
#endif
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

/*----------------------------------------------------------------*/

typedef enum { SHADOWED_WINDOW,
       	       TITLED_WINDOW,
       	       BORDERED_WINDOW,
       	       MODAL_WINDOW,
       	       BACKDROP_WINDOW,
       	       QUERY_WINDOW } window_type;

/*----------------------------------------------------------------*/
/* window part codes */

enum {
	UNKNOWN_AREA,
	TITLE_BAR,
	CONTENT_AREA,
	RESIZE_AREA,
	CLOSE_BOX
};

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
const long FLOATS = 0x00000080;

/*----------------------------------------------------------------*/

struct message;
class _BSession;
class BMenuItem;
class BMenuBar;
struct CommandKey;

/*----------------------------------------------------------------*/

class BWindow : public BObject {
	DECLARE_CLASS_INFO(BObject);

public:
						BWindow(BRect frame,
								const char *title, 
								window_type type,
								ulong flags);
						BWindow();
virtual					~BWindow();

virtual	void			Close();

virtual	bool			FilterKeyDown(ulong *aKey, BView **targetView);	
virtual	bool			FilterMouseDown(BPoint loc, BView **targetView);
virtual	bool			FilterMessageDropped(	BPoint loc,
												BMessage *a_message,
												BView **targetView);
virtual	bool			FilterMouseMoved(	BPoint loc,
											ulong code,
											BMessage *a_message,
											BView **targetView);
virtual	void			AddChild(BView *);
virtual	bool			RemoveChild(BView *);
		long			CountChildren() const;
		BView			*ChildAt(long index) const;
virtual	void			DispatchMessage(BMessage *);
virtual void			MessageReceived(BMessage *);
virtual	void			FrameMoved(BPoint new_position);
virtual	void			FrameResized(long new_width, long new_height);		
virtual	bool			CloseRequested(bool quitting = FALSE);	
		void			SetPulseRate(long rate);
		void			PostMessage(BMessage *);
		void			PostMessage(BMessage *, BView *);
		void			PostMessage(ulong command);
		void			PostMessage(ulong command, BView *);
		BMessage		*CurrentMessage() const;
		BMessage		*DetachCurrentMessage();
		bool			LoadFromResource(long resID);
		void			AddShortcut(	ulong key,
										ulong modifiers,
										ulong cmd);
		void			AddShortcut(	ulong key,
										ulong modifiers,
										BMenuItem *item);
		void			RemoveShortcut(ulong key, ulong modifiers);
virtual	void			SetupMenus();
		ulong			Modifiers() const;
		bool			NeedsUpdate() const;
		void			UpdateIfNeeded();
		BView			*FindView(const char *view_name) const;
		BView			*FindView(BPoint) const;
		BView			*CurrentFocus() const;
		bool			Lock();
		void			Unlock();
		void			Flush() const;
		void			Activate(bool = TRUE);
virtual	void			WindowActivated(bool state);
		void			ConvertToScreen(BPoint* ) const;
		void			ConvertFromScreen(BPoint* ) const;
		void			ConvertToScreen(BRect *) const;
		void			ConvertFromScreen(BRect *) const;
		void			MoveBy(long dx, long dy);
		void			MoveTo(BPoint);
		void			MoveTo(long x, long y);
		void			ResizeBy(long dx, long dy);
		void			ResizeTo(long width, long height);
virtual	void			Show();
virtual	void			Hide();
		bool			IsHidden() const;
		void			DisableUpdates();
		void			EnableUpdates();
		BRect			Bounds() const;
		BRect			Frame() const;
		void			GetTitle(char *) const;
		void			SetTitle(const char *);
		bool			IsFront() const;
		bool			IsActive() const;
		BMessageQueue	*MessageQueue() const;
		void			RemoveMouseEvents();
		void			SetMainMenuBar(BMenuBar *bar);

// ------------------------------------------------------------------

private:

friend class BApplication;
friend class BImageBuffer;
friend class BScrollBar;
friend class BView;
friend BView *EditViewCreate(BRect frame,
								const char *name,
								ulong resizeMask,
								ulong flags,
								void *resData,
								long id);

		long		Token() const;
		bool		SaveAsResource(long resID);
		void		close1();
static	void		_task0_();
		void		task();
		void		set_brol(BMessage *msg, long vs_token, BRect track_rect);
		void		set_brol(	BMessage *msg,
								long vs_token,
								long dh,
								long dv,
								long bitmap_token);
		void		set_brol(BMessage *);
		void		force_drag();
		void		view_builder(BView *a_view);
		long		get_server_token() const;
		void		do_drop(BMessage *an_event);
		void		movesize(long opcode, long h, long v);
		//void		do_gen_event(message *a_message);
		
		void		handle_activate(BMessage *an_event);
		void		do_view_frame(BMessage *an_event);
		void		do_value_change(BMessage *an_event);
		void		do_mouse_down(BMessage *an_event);
		void		do_mouse_moved(BMessage *an_event);
		void		do_key_down(BMessage *an_event);
		void		do_draw_view(message *a_message);
		void		do_close_requested();
		void		queue_new_message(message *a_message);
		void		queue_event_message(message *a_message);
		void		dequeue_as_much_as_possible();
		void		lock_private();
		void		DoPulse();
		CommandKey	*allocShortcut(ulong key, ulong modifiers);
		void		post_message(BMessage *message);
		
		long			signature;
		BWindow			*next_window;
		BMessageQueue	*message_queue;
		BMessage		*last_message;	
		long			server_token;
		long			client_token;
		char			update_buzy;
		char			f_active;
		short			fShowLevel;
		ulong			fFlags;

		long			send_port;
		long			receive_port;
		long			inter_port;
		long			task_id;
		long			lock_sem;
		long			lock_owner_count;
		long			lock_owner;
		bool			closing;
		long			close_sem;

		BView			*top_view;
		BView			*focus;
		BView			*last_mm_target;
		_BSession		*a_session;
		BMessage		*last_tbrol;
		BMenuBar		*fMainMenuBar;
		BList			accelList;
		long			last_vs_token;
		long			drag_bitmap_token;
		BRect			last_drag_rect;
		long			drag_dh;
		long			drag_dv;
		long			id;
		long			top_view_token;
		long			pulse_phase;
		long			pulse_rate;
		bool			discipline;
};

//------------------------------------------------------------------------------

#endif
