//******************************************************************************
//
//	File:		Window.h
//
//	Description:	Client window class.
//
//	Copyright 1992-96, Be Incorporated, All Rights Reserved.
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
#include <MessageQueue.h>
#endif
#ifndef	_LOOPER_H
#include <Looper.h>
#endif
#ifndef _MESSAGE_H
#include <Message.h>
#endif
#ifndef _LIST_H
#include <List.h>
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif
#ifndef _CLIPBOARD_H
#include <Clipboard.h>
#endif

/*----------------------------------------------------------------*/

typedef enum { B_SHADOWED_WINDOW,
       	       B_TITLED_WINDOW,
       	       B_BORDERED_WINDOW,
       	       B_MODAL_WINDOW,
       	       B_BACKDROP_WINDOW,
       	       B_QUERY_WINDOW } window_type;

/*----------------------------------------------------------------*/
/* window part codes */

enum {
	B_UNKNOWN_AREA,
	B_TITLE_AREA,
	B_CONTENT_AREA,
	B_RESIZE_AREA,
	B_CLOSE_AREA,
	B_ZOOM_AREA,
	B_MINIMIZE_AREA
};

/*----------------------------------------------------------------*/
/* window manager flags for windows properties			  */
/*----------------------------------------------------------------*/

const long B_NOT_MOVABLE				= 0x00000001;
const long B_NOT_H_RESIZABLE			= 0x00000004;
const long B_NOT_V_RESIZABLE			= 0x00000008;
const long B_NOT_RESIZABLE				= 0x00000002;
const long B_WILL_ACCEPT_FIRST_CLICK	= 0x00000010;
const long B_NOT_CLOSABLE			= 0x00000020;
const long B_NOT_ZOOMABLE			= 0x00000040;
const long B_NOT_MINIMIZABLE		= 0x00004000;
const long B_WILL_FLOAT				= 0x00000080;
const long _PRIVATE_W_FLAG1_		= 0x00000100;
const long _PRIVATE_W_FLAG2_		= 0x00000200;
const long _PRIVATE_W_FLAG3_		= 0x00000400;
const long _PRIVATE_W_FLAG4_		= 0x00000800;
const long _PRIVATE_W_FLAG5_		= 0x00001000;
const long _PRIVATE_W_FLAG6_		= 0x00002000;
const long _PRIVATE_W_FLAG7_		= 0x10000000;
const long _PRIVATE_W_FLAG8_		= 0x20000000;

/*----------------------------------------------------------------*/

struct message;
class _BSession;
class BMenuItem;
class BMenuBar;
class BButton;
class BDirectory;
struct _cmd_key_;

/*----------------------------------------------------------------*/

class BWindow : public BLooper {
	B_DECLARE_CLASS_INFO(BLooper);

public:
						BWindow(BRect frame,
								const char *title, 
								window_type type,
								ulong flags);
virtual					~BWindow();

virtual	void			Quit();
		void			Close();
		void			SetDiscipline(bool yesno);

		long			RunSavePanel(	const char* save_name = NULL,
										const char* title = NULL,
										const char* button_name = NULL,
										BMessage* configuration = NULL);
		bool			IsSavePanelRunning() const;
		void			CloseSavePanel();
virtual	void			SaveRequested(record_ref directory, const char *name);
virtual	void			SavePanelClosed(BMessage* message);

virtual	bool			FilterKeyDown(ulong *aKey, BView **targetView);	
virtual	bool			FilterMouseDown(BPoint loc, BView **targetView);
virtual	bool			FilterMouseMoved(	BPoint loc,
											ulong code,
											BMessage *a_message,
											BView **targetView);
virtual	bool			FilterMessageDropped(	BMessage *a_message,
												BPoint loc,
												BView **targetView);

virtual	void			AddChild(BView *view);
virtual	bool			RemoveChild(BView *view);
		long			CountChildren() const;
		BView			*ChildAt(long index) const;
virtual	void			DispatchMessage(BMessage *message, BReceiver *receiver);
virtual	void			FrameMoved(BPoint new_position);
virtual	void			FrameResized(float new_width, float new_height);
virtual void			Minimize(bool minimize);
virtual void			Zoom(	BPoint rec_position,
								float rec_width,
								float rec_height);
		void			Zoom();
		void			SetZoomLimits(float max_h, float max_v);
virtual void			ScreenChanged(BRect screen_size, color_space depth);
		void			SetPulseRate(long rate);
		void			AddShortcut(	ulong key,
										ulong modifiers,
										BMessage *msg);
		void			AddShortcut(	ulong key,
										ulong modifiers,
										BMessage *msg,
										BReceiver *target);
		void			RemoveShortcut(ulong key, ulong modifiers);
		void			SetDefaultButton(BButton *button);
		BButton			*DefaultButton() const;
virtual	void			MenusWillShow();
		ulong			Modifiers() const;
		bool			NeedsUpdate() const;
		void			UpdateIfNeeded();
		BView			*FindView(const char *view_name) const;
		BView			*FindView(BPoint) const;
		BView			*CurrentFocus() const;
		BReceiver		*PreferredReceiver() const;
		void			Flush() const;
		void			Activate(bool = TRUE);
virtual	void			WindowActivated(bool state);
		void			ConvertToScreen(BPoint* ) const;
		void			ConvertFromScreen(BPoint* ) const;
		void			ConvertToScreen(BRect *) const;
		void			ConvertFromScreen(BRect *) const;
		void			MoveBy(float dx, float dy);
		void			MoveTo(BPoint);
		void			MoveTo(float x, float y);
		void			ResizeBy(float dx, float dy);
		void			ResizeTo(float width, float height);
virtual	void			Show();
virtual	void			Hide();
		bool			IsHidden() const;
		void			DisableUpdates();
		void			EnableUpdates();
		BRect			Bounds() const;
		BRect			Frame() const;
		const char		*Title() const;
		void			SetTitle(const char *title);
		bool			IsFront() const;
		bool			IsActive() const;
		void			RemoveMouseMessages();
		void			SetMainMenuBar(BMenuBar *bar);
		void			SetSizeLimits(	float min_h,
										float max_h,
										float min_v,
										float max_v);

// ------------------------------------------------------------------

private:

friend class BApplication;
friend class BBitmap;
friend class BScrollBar;
friend class BView;
friend class BMenuItem;
friend void _set_menu_sem_(BWindow *w, sem_id sem);

					BWindow(BRect frame, color_space depth);
		void		BitmapClose();
virtual	void		task_looper();
		void		start_drag(	BMessage *msg,
								long token,
								BPoint offset,
								BRect track_rect);
		void		start_drag(	BMessage *msg,
								long token,
								BPoint offset,
								long bitmap_token);
		void		view_builder(BView *a_view);
		long		get_server_token() const;
		void		do_drop(BMessage *an_event);
		void		movesize(long opcode, float h, float v);
		
		void		handle_activate(BMessage *an_event);
		void		do_view_frame(BMessage *an_event);
		void		do_value_change(BMessage *an_event);
		void		do_mouse_down(BMessage *an_event);
		void		do_mouse_moved(BMessage *an_event);
		void		do_key_down(BMessage *an_event);
		void		do_menu_event(BMessage *an_event);
		void		do_draw_view(message *a_message);
		void		queue_new_message(message *a_message);
		void		queue_event_message(message *a_message);
		void		dequeue_as_much_as_possible();
		void		DoPulse();
		_cmd_key_	*allocShortcut(ulong key, ulong modifiers);
		_cmd_key_	*FindShortcut(ulong key, ulong modifiers);
		void		AddShortcut(ulong key,
								ulong modifiers,
								BMenuItem *item);
		void		post_message(BMessage *message);
		void		tickle();
		void		SetLocalTitle(const char *new_title);

		char			*fTitle;
		long			server_token;
		char			update_buzy;
		char			f_active;
		short			fShowLevel;
		ulong			fFlags;

		long			send_port;
		long			receive_port;
		long			task_id;

		BView			*top_view;
		BView			*focus;
		BView			*last_mm_target;
		_BSession		*a_session;
		BMenuBar		*fMainMenuBar;
		BButton			*fDefaultButton;
		BList			accelList;
		long			top_view_token;
		long			pulse_phase;
		long			pulse_rate;
		bool			discipline;
		bool			fWaitingForMenu;
		bool			fSavePanelOpen;
		record_ref		fLastSavePanelDir;
		bool			fOffscreen;
		sem_id			fMenuSem;
		float			fMaxZoomH;
		float			fMaxZoomV;
		float			fMaxWindH;
		float			fMaxWindV;
		BRect			fFrame;
		window_type		fType;
};

//------------------------------------------------------------------------------

inline void  BWindow::Close()			{ Quit(); }

//------------------------------------------------------------------------------

#endif
