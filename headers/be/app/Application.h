/*******************************************************************************
//
//	File:			Application.h
//
//	Description:	Client application class.
//
//	Copyright 1992-97, Be Incorporated, All Rights Reserved.
//
//*****************************************************************************/


#ifndef	_APPLICATION_H
#define	_APPLICATION_H

#include <StorageDefs.h>
#include <InterfaceDefs.h>
#include <Rect.h>
#include <Point.h>
#include <Looper.h>
#include <Window.h>
#include <OS.h>
#include <Messenger.h>
#include <Roster.h>
#include <PopUpMenu.h>

class BDirectory;

//------------------------------------------------------------------------------

class BView;
class BRect;
class BList;
class _BSession_;
class BWindow;

//------------------------------------------------------------------------------

class BApplication : public BLooper {

public:
						BApplication(uint32 signature);
						BApplication(const char *signature);
virtual					~BApplication();

						BApplication(BMessage *data);
static	BApplication	*Instantiate(BMessage *data);
virtual	status_t		Archive(BMessage *data, bool deep = true) const;

virtual	thread_id		Run();
virtual	void			Quit();
virtual bool			QuitRequested();
virtual	void			Pulse();
virtual	void			ReadyToRun();
virtual	void			MessageReceived(BMessage *msg);
virtual	void			ArgvReceived(int32 argc, char **argv);
virtual	void			AppActivated(bool active);
virtual	void			RefsReceived(BMessage *a_message);
virtual	void			AboutRequested();

virtual BHandler		*ResolveSpecifier(BMessage *msg,
										int32 index,
										BMessage *specifier,
										int32 form,
										const char *property);

		bool			IsLaunching() const;
		status_t		GetAppInfo(app_info *info) const;
		void			ShowCursor();
		void			HideCursor();
		void			ObscureCursor();
		bool			IsCursorHidden() const;
		void			SetCursor(const void *cursor);
		int32			CountWindows() const;
		BWindow			*WindowAt(int32 index) const;
virtual	void			DispatchMessage(BMessage *an_event,
										BHandler *handler);
		void			SetPulseRate(bigtime_t rate);

virtual status_t		GetSupportedSuites(BMessage *data);
virtual status_t		Perform(uint32 d, void *arg);

// ------------------------------------------------------------------

private:

friend class BWindow;
friend class BView;
friend class BScrollBar;
friend long _pulse_task_(void *arg);
friend void _toggle_handles_(bool);
						
						BApplication(const BApplication &);
		BApplication	&operator=(const BApplication &);

virtual	void			_ReservedApplication1();
virtual	void			_ReservedApplication2();
virtual	void			_ReservedApplication3();
virtual	void			_ReservedApplication4();
virtual	void			_ReservedApplication5();
virtual	void			_ReservedApplication6();
virtual	void			_ReservedApplication7();
virtual	void			_ReservedApplication8();

virtual	bool			ScriptReceived(BMessage *msg,
										int32 index,
										BMessage *specifier,
										int32 form,
										const char *property);
		void			run_task();
		void			InitData(const char *signature);
		void			BeginRectTracking(BRect r, bool trackWhole);
		void			EndRectTracking();
		void			pulse_task();
		void			get_scs();
		void			send_drag(	BMessage *msg,
									int32 vs_token,
									BPoint offset,
									BRect drag_rect,
									BHandler *reply_to);
		void			send_drag(	BMessage *msg,
									int32 vs_token,
									BPoint offset,
									int32 bitmap_token,
									BHandler *reply_to);
		void			write_drag(_BSession_ *session, BMessage *a_message);
		bool			quit_all_windows(bool request, bool incl_menu = FALSE);
		void			do_argv(BMessage *msg);
		void			SetAppCursor();
		void			enable_pulsing(bool enable);
		uint32			InitialWorkspace();
		int32			count_windows(bool incl_menus) const;
		BWindow			*window_at(uint32 index, bool incl_menus) const;
		status_t		get_window_list(BList *list, bool incl_menus) const;

		const char		*fAppName;
		int32			fServerFrom;
		int32			fServerTo;
		void			*fCursorData;
		thread_id		fPulseTaskID;
		int32			fPulseEnabledCount;
		bigtime_t		fPulseRate;
		int32			fPulsePhase;
		uint32			fInitialWorkspace;
		uint32			_reserved[12];

		bool			fReadyToRunCalled;
};

//------------------------------------------------------------------------------

extern BApplication	*be_app;
extern BMessenger	be_app_messenger;

//------------------------------------------------------------------------------

#endif
