//******************************************************************************
//
//	File:		Window.h
//
//	Description:	Client window class.
//
//	Copyright 1992-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#pragma once

#ifndef	_WINDOW_H
#define	_WINDOW_H

#include <StorageDefs.h>
#include <InterfaceDefs.h>
#include <Rect.h>
#include <View.h>
#include <MessageQueue.h>
#include <Looper.h>
#include <Message.h>
#include <Messenger.h>
#include <Clipboard.h>
#include <List.h>

/*----------------------------------------------------------------*/

enum window_type {
	B_TITLED_WINDOW = 1,
	B_MODAL_WINDOW = 3,
	B_DOCUMENT_WINDOW = 11,
	B_BORDERED_WINDOW = 20
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
struct _view_attr_;

/*----------------------------------------------------------------*/

class BWindow : public BLooper {

public:
						BWindow(BRect frame,
								const char *title, 
								window_type type,
								uint32 flags,
								uint32 workspace = B_CURRENT_WORKSPACE);
virtual					~BWindow();

						BWindow(BMessage *data);
static	BWindow			*Instantiate(BMessage *data);
virtual	status_t		Archive(BMessage *data, bool deep = true) const;

virtual	void			Quit();
		void			Close();
		window_type		WindowType() const;

		void			AddChild(BView *child, BView *before = NULL);
		bool			RemoveChild(BView *child);
		int32			CountChildren() const;
		BView			*ChildAt(int32 index) const;

virtual	void			DispatchMessage(BMessage *message, BHandler *handler);
virtual	void			MessageReceived(BMessage *message);
virtual	void			FrameMoved(BPoint new_position);
virtual void			WorkspacesChanged(uint32 old_ws, uint32 new_ws);
virtual void			WorkspaceActivated(int32 ws, bool state);
virtual	void			FrameResized(float new_width, float new_height);
virtual void			Minimize(bool minimize);
virtual void			Zoom(	BPoint rec_position,
								float rec_width,
								float rec_height);
		void			Zoom();
		void			SetZoomLimits(float max_h, float max_v);
virtual void			ScreenChanged(BRect screen_size, color_space depth);
		void			SetPulseRate(bigtime_t rate);
		bigtime_t		PulseRate() const;
		void			AddShortcut(	uint32 key,
										uint32 modifiers,
										BMessage *msg);
		void			AddShortcut(	uint32 key,
										uint32 modifiers,
										BMessage *msg,
										BHandler *target);
		void			RemoveShortcut(uint32 key, uint32 modifiers);
		void			SetDefaultButton(BButton *button);
		BButton			*DefaultButton() const;
virtual	void			MenusBeginning();
virtual	void			MenusEnded();
		bool			NeedsUpdate() const;
		void			UpdateIfNeeded();
		BView			*FindView(const char *view_name) const;
		BView			*FindView(BPoint) const;
		BView			*CurrentFocus() const;
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
		uint32			Workspaces() const;
		void			SetWorkspaces(uint32);

virtual BHandler		*ResolveSpecifier(BMessage *msg,
										int32 index,
										BMessage *specifier,
										int32 form,
										const char *property);
virtual status_t		GetSupportedSuites(BMessage *data);

		void			AddFloater(BWindow *a_floating_window);
		void			RemoveFloater(BWindow *a_floating_window);

virtual status_t		Perform(uint32 d, void *arg);

// ------------------------------------------------------------------

private:

friend class BApplication;
friend class BBitmap;
friend class BScrollBar;
friend class BView;
friend class BMenuItem;
friend class BWindowScreen;
friend void _set_menu_sem_(BWindow *w, sem_id sem);

virtual	void			_ReservedWindow1();
virtual	void			_ReservedWindow2();
virtual	void			_ReservedWindow3();
virtual	void			_ReservedWindow4();
virtual	void			_ReservedWindow5();
virtual	void			_ReservedWindow6();
virtual	void			_ReservedWindow7();
virtual	void			_ReservedWindow8();

					BWindow();
					BWindow(BWindow &);
		BWindow		&operator=(BWindow &);
					
					BWindow(BRect frame, color_space depth);
		void		InitData(BRect frame,
							const char *title, 
							window_type type,
							uint32 flags,
							uint32 workspace);
		status_t	ArchiveChildren(BMessage *data, bool deep) const;
		status_t	UnarchiveChildren(BMessage *data);
		void		BitmapClose();
virtual	void		task_looper();
		void		start_drag(	BMessage *msg,
								int32 token,
								BPoint offset,
								BRect track_rect,
								BHandler *reply_to);
		void		start_drag(	BMessage *msg,
								int32 token,
								BPoint offset,
								int32 bitmap_token,
								BHandler *reply_to);
		void		view_builder(BView *a_view);
		void		attach_builder(BView *a_view);
		void		detach_builder(BView *a_view);
		int32		get_server_token() const;
		BMessage	*extract_drop(BMessage *an_event, BHandler **target);
		void		movesize(uint32 opcode, float h, float v);
		
		void		handle_activate(BMessage *an_event);
		void		do_view_frame(BMessage *an_event);
		void		do_value_change(BMessage *an_event, BHandler *handler);
		void		do_mouse_down(BMessage *an_event, BView *target);
		void		do_mouse_moved(BMessage *an_event, BView *target);
		void		do_key_down(BMessage *an_event, BHandler *handler);
		void		do_key_up(BMessage *an_event, BHandler *handler);
		void		do_menu_event(BMessage *an_event);
		void		do_draw_views(message *a_message);
virtual BMessage	*ConvertToMessage(void *raw, int32 code);
		_cmd_key_	*allocShortcut(uint32 key, uint32 modifiers);
		_cmd_key_	*FindShortcut(uint32 key, uint32 modifiers);
		void		AddShortcut(uint32 key,
								uint32 modifiers,
								BMenuItem *item);
		void		post_message(BMessage *message);
		void		SetLocalTitle(const char *new_title);
		void		enable_pulsing(bool enable);
		BHandler	*determine_target(BMessage *msg, BHandler *target);
		void		kb_navigate();
		void		navigate_to_next(int32 direction, bool group = FALSE);
		void		set_focus(BView *focus);
		bool		InUpdate();
		void		DequeueAll();
		void		find_token_and_handler(BMessage *msg,
											int32 *token,
											BHandler **handler);

		char			*fTitle;
		int32			server_token;
		char			fInUpdate;
		char			f_active;
		short			fShowLevel;
		uint32			fFlags;

		port_id			send_port;
		port_id			receive_port;

		BView			*top_view;
		BView			*fFocus;
		BView			*last_mm_target;
		_BSession_		*a_session;
//+		void			*fMsgBuffer;
//+		int32			fMsgBufferSize;
		BMenuBar		*fKeyMenuBar;
		BButton			*fDefaultButton;
		BList			accelList;
		int32			top_view_token;
		bool			pulse_enabled;
		int32			pulse_phase;
		int32			pulse_queued;
		bigtime_t		pulse_rate;
		bool			fWaitingForMenu;
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
		_view_attr_		*fCurDrawViewState;

		uint32			_reserved[8];
};

//------------------------------------------------------------------------------

inline void  BWindow::Close()			{ Quit(); }		// OK, no private parts

//------------------------------------------------------------------------------

#endif
