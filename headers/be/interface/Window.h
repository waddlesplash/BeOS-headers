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
#ifndef _MESSENGER_H
#include <Messenger.h>
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

enum window_type {
	B_TITLED_WINDOW = 1,
	B_BORDERED_WINDOW = 2,
	B_MODAL_WINDOW = 3,
	B_DOCUMENT_WINDOW = 11
};

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

enum {
	B_NOT_MOVABLE				= 0x00000001,
	B_NOT_RESIZABLE				= 0x00000002,
	B_NOT_H_RESIZABLE			= 0x00000004,
	B_NOT_V_RESIZABLE			= 0x00000008,
	B_WILL_ACCEPT_FIRST_CLICK	= 0x00000010,
	B_NOT_CLOSABLE				= 0x00000020,
	B_NOT_ZOOMABLE				= 0x00000040,
	B_NOT_MINIMIZABLE			= 0x00004000,
	B_WILL_FLOAT				= 0x00000080,
	_PRIVATE_W_FLAG1_			= 0x00000100,
	_PRIVATE_W_FLAG2_			= 0x00000200,
	_PRIVATE_W_FLAG3_			= 0x00000400,
	_PRIVATE_W_FLAG4_			= 0x00000800,
	_PRIVATE_W_FLAG5_			= 0x00001000,
	_PRIVATE_W_FLAG6_			= 0x00002000,
	_PRIVATE_W_FLAG7_			= 0x10000000,
	_PRIVATE_W_FLAG8_			= 0x20000000,
	_PRIVATE_W_FLAG9_			= 0x00008000
};

#define B_CURRENT_WORKSPACE	0
#define B_ALL_WORKSPACES	0xffffffff

/*----------------------------------------------------------------*/

struct message;
class _BSession_;
class BMenuItem;
class BMenuBar;
class BButton;
struct _cmd_key_;

/*----------------------------------------------------------------*/

class BWindow : public BLooper {

public:
						BWindow(BRect frame,
								const char *title, 
								window_type type,
								ulong flags,
								ulong workspace = B_CURRENT_WORKSPACE);
virtual					~BWindow();

virtual	void			Quit();
		void			Close();
		void			SetDiscipline(bool yesno);
		window_type		WindowType() const;

		long			RunSavePanel(	const char* save_name = NULL,
										const char* title = NULL,
										const char* button_name = NULL,
										const char* cancel_button_name = NULL,
										BMessage* configuration = NULL);
		bool			IsSavePanelRunning();
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

virtual	void			DispatchMessage(BMessage *message, BHandler *handler);
virtual	void			MessageReceived(BMessage *message);
virtual	void			FrameMoved(BPoint new_position);
virtual void			WorkspacesChanged(ulong old_ws, ulong new_ws);
virtual void			WorkspaceActivated(long ws, bool state);
virtual	void			FrameResized(float new_width, float new_height);
virtual void			Minimize(bool minimize);
virtual void			Zoom(	BPoint rec_position,
								float rec_width,
								float rec_height);
		void			Zoom();
		void			SetZoomLimits(float max_h, float max_v);
virtual void			ScreenChanged(BRect screen_size, color_space depth);
		void			SetPulseRate(double rate);
		double			PulseRate() const;
		void			AddShortcut(	ulong key,
										ulong modifiers,
										BMessage *msg);
		void			AddShortcut(	ulong key,
										ulong modifiers,
										BMessage *msg,
										BHandler *target);
		void			RemoveShortcut(ulong key, ulong modifiers);
		void			SetDefaultButton(BButton *button);
		BButton			*DefaultButton() const;
virtual	void			MenusWillShow();
		bool			NeedsUpdate() const;
		void			UpdateIfNeeded();
		BView			*FindView(const char *view_name) const;
		BView			*FindView(BPoint) const;
		BView			*CurrentFocus() const;
		BHandler		*PreferredHandler() const;
		void			Flush() const;
		void			Activate(bool = TRUE);
virtual	void			WindowActivated(bool state);
		void			ConvertToScreen(BPoint *pt) const;
		BPoint			ConvertToScreen(BPoint pt) const;
		void			ConvertFromScreen(BPoint *pt) const;
		BPoint			ConvertFromScreen(BPoint pt) const;
		void			ConvertToScreen(BRect *rect) const;
		BRect			ConvertToScreen(BRect rect) const;
		void			ConvertFromScreen(BRect *rect) const;
		BRect			ConvertFromScreen(BRect rect) const;
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
		void			SetKeyMenuBar(BMenuBar *bar);
		BMenuBar		*KeyMenuBar() const;
		void			SetSizeLimits(	float min_h,
										float max_h,
										float min_v,
										float max_v);
		void			GetSizeLimits(	float *min_h,
										float *max_h,
										float *min_v,
										float *max_v);
		ulong			Workspaces() const;
		void			SetWorkspaces(ulong);

virtual	void			HandlersRequested(BMessage *msg);

// ------------------------------------------------------------------

private:

friend class BApplication;
friend class BBitmap;
friend class BScrollBar;
friend class BView;
friend class BMenuItem;
friend class BWindowScreen;
friend void _set_menu_sem_(BWindow *w, sem_id sem);

					BWindow(BRect frame, color_space depth);
		void		BitmapClose();
virtual	void		task_looper();
		void		start_drag(	BMessage *msg,
								long token,
								BPoint offset,
								BRect track_rect,
								BHandler *reply_to);
		void		start_drag(	BMessage *msg,
								long token,
								BPoint offset,
								long bitmap_token,
								BHandler *reply_to);
		void		view_builder(BView *a_view);
		void		attach_builder(BView *a_view);
		void		detach_builder(BView *a_view);
		long		get_server_token() const;
		BMessage	*extract_drop(BMessage *an_event, BHandler **target);
		void		movesize(long opcode, float h, float v);
		
		void		handle_activate(BMessage *an_event);
		void		do_view_frame(BMessage *an_event);
		void		do_value_change(BMessage *an_event, BHandler *handler);
		void		do_mouse_down(BMessage *an_event, BView *target);
		void		do_mouse_moved(BMessage *an_event, BView *target);
		void		do_key_down(BMessage *an_event, BHandler *handler);
		void		do_menu_event(BMessage *an_event);
		void		do_draw_view(message *a_message);
		void		*read_message(long *code);
		void		queue_new_message(void *data);
		void		queue_event_message(void *data, long code);
		void		DoPulse();
		_cmd_key_	*allocShortcut(ulong key, ulong modifiers);
		_cmd_key_	*FindShortcut(ulong key, ulong modifiers);
		void		AddShortcut(ulong key,
								ulong modifiers,
								BMenuItem *item);
		void		post_message(BMessage *message);
		void		SetLocalTitle(const char *new_title);
		void		enable_pulsing(bool enable);
		BHandler	*determine_target(BMessage *msg, BHandler *target);
		void		kb_navigate();
		void		navigate_to_next(long direction);

		char			*fTitle;
		long			server_token;
		char			update_buzy;
		char			f_active;
		short			fShowLevel;
		ulong			fFlags;

		long			send_port;
		long			receive_port;

		BView			*top_view;
		BView			*focus;
		BView			*last_mm_target;
		_BSession_		*a_session;
		void			*fBuffer;
		long			fBufferSize;
		BMenuBar		*fKeyMenuBar;
		BButton			*fDefaultButton;
		BList			accelList;
		long			top_view_token;
		bool			pulse_enabled;
		long			pulse_phase;
		double			pulse_rate;
		bool			discipline;
		bool			fWaitingForMenu;
		BMessenger		fPanelMessenger;
		record_ref		fLastSavePanelDir;
		bool			fOffscreen;
		sem_id			fMenuSem;
		float			fMaxZoomH;
		float			fMaxZoomV;
		float			fMinWindH;
		float			fMinWindV;
		float			fMaxWindH;
		float			fMaxWindV;
		BRect			fFrame;
		window_type		fType;
};

//------------------------------------------------------------------------------

inline void  BWindow::Close()			{ Quit(); }
inline window_type  BWindow::WindowType() const		{ return fType; }

//------------------------------------------------------------------------------

#endif
