//******************************************************************************
//
//	File:			Application.h
//
//	Description:	Client application class.
//
//	Copyright 1992-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_APPLICATION_H
#define	_APPLICATION_H

#ifndef _STORAGE_DEFS_H
#include <StorageDefs.h>
#endif

#ifndef _INTERFACE_DEFS_H
#include <InterfaceDefs.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _LOOPER_H
#include <Looper.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef _OS_H
#include <OS.h>
#endif

#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

#ifndef _MESSENGER_H
#include <Messenger.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif

#ifndef _POP_UP_MENU_H
#include <PopUpMenu.h>
#endif

class BDirectory;

//------------------------------------------------------------------------------

class BView;

class BRect;
class BList;
class _BSession;
class BWindow;

//------------------------------------------------------------------------------

class BApplication : public BLooper {
	B_DECLARE_CLASS_INFO(BLooper);

public:
						BApplication(ulong signature);
virtual					~BApplication();

virtual	thread_id		Run();
virtual	void			Quit();
virtual bool			QuitRequested();
virtual	void			Pulse();
virtual	void			ReadyToRun();
virtual	void			ArgvReceived(int argc, char **argv);
virtual	void			Activate();
virtual	void			AppActivated(bool active);
virtual	void			RefsReceived(BMessage *a_message);
virtual	void			FilePanelClosed(BMessage *a_message);
virtual	void			AboutRequested();

virtual	void			HandlersRequested(BMessage *msg);

		bool			IsLaunching() const;

		long			GetAppInfo(app_info *info);

		long			RunFilePanel(	const char* title = NULL,
										const char* button_name = NULL,
										const char* cancel_button_name = NULL,
										bool directories_only = FALSE,
										BMessage* configuration = NULL);

		bool			IsFilePanelRunning();
		void			CloseFilePanel();

		void			ShowCursor();
		void			HideCursor();
		void			ObscureCursor();
		bool			IsCursorHidden() const;
		void			SetCursor(const void *cursor);
		long			CountWindows() const;
		BWindow			*WindowAt(long index) const;
virtual	void			DispatchMessage(BMessage *an_event,
										BHandler *handler);
		void			SetPulseRate(double rate);

virtual	void			VolumeMounted(long volid);
virtual	void			VolumeUnmounted(long volid);

		void			SetMainMenu(BPopUpMenu *menu);
		BPopUpMenu		*MainMenu();
virtual	void			MenusWillShow();

// ------------------------------------------------------------------

private:

friend BView *EditViewCreate(	BRect frame,
								char *name,
								ulong resizeMask,
								ulong flags,
								void *resData,
								long id);

friend class BWindow;
friend class BView;
friend class BScrollBar;
friend long _main_menu_task_(void *arg);
friend long _pulse_task_(void *arg);

		void			run_task();
		long			OpenResourceFile(char *name = (char *) 0);
		long			LoadResource(ulong type, ulong id, void **p, long *len);
		long			AddResource(ulong type, ulong id, void *buf, long len);
		long			DeleteResource(ulong type, ulong id);
		void			BeginRectTracking(BRect r, bool trackWhole);
		void			EndRectTracking();
		void			pulse_task();
		void			get_scs();
		void			get_key_trans_maps();
		void			send_drag(	BMessage *msg,
									long vs_token,
									BPoint offset,
									BRect drag_rect,
									BHandler *reply_to);
		void			send_drag(	BMessage *msg,
									long vs_token,
									BPoint offset,
									long bitmap_token,
									BHandler *reply_to);
		void			write_drag(_BSession *the_session, BMessage *a_message);
		bool			quit_all_windows(bool makeRequest);
		void			do_argv(BMessage *msg);
		BPopUpMenu		*MakeDefaultMainMenu();
		void			SetAppCursor();
		void			enable_pulsing(bool enable);
		ulong			InitialWorkspace();

		BPopUpMenu		*fMainMenu;
		const char		*fAppName;
		long			fServerFrom;
		long			fServerTo;
		void			*fCursorData;
		thread_id		fMainMenuTaskID;
		sem_id			fMainMenuSem;
		thread_id		fPulseTaskID;
		long			fPulseEnabledCount;
		double			fPulseRate;
		long			fPulsePhase;
		ulong			fInitialWorkspace;
		bool			fReadyToRunCalled;
		BMessenger		fPanelMessenger;
		record_ref		fLastOpenPanelDir;
};

//------------------------------------------------------------------------------

extern BApplication *be_app;

//------------------------------------------------------------------------------

#endif
