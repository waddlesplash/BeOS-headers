/*******************************************************************************
/
/	File:			TabView.h
/
/   Description:    BTab creates individual "tabs" that can be assigned
/                   to specific views.
/                   BTabView provides the framework for containing and
/                   managing groups of BTab objects.
/
/	Copyright 1997-98, Be Incorporated, All Rights Reserved
/
/******************************************************************************/

#ifndef _TAB_VIEW_H
#define _TAB_VIEW_H

#include <BeBuild.h>
#include <Message.h>
#include <View.h>

/*----------------------------------------------------------------*/
/*----- tab definitions ------------------------------------------*/

enum tab_position {
	B_TAB_FIRST = 999,
	B_TAB_FRONT,
	B_TAB_ANY
};

/*----------------------------------------------------------------*/
/*----- BTab class -----------------------------------------------*/


class BTab : public BArchivable {
public:
						BTab(BView* v=NULL);
virtual					~BTab();

						BTab(BMessage* data);
static 	BArchivable*	Instantiate(BMessage* data);
virtual	status_t		Archive(BMessage* data, bool deep = true) const;
virtual status_t		Perform(uint32 d, void *arg);

		const char* 	Label() const;
virtual	void			SetLabel(const char* label);

		bool			IsSelected() const;
virtual	void			Select(BView*);
virtual	void			Deselect();

virtual	void			SetEnabled(bool on);
		bool			IsEnabled() const;
		
		void			MakeFocus(bool infocus=true);
		bool			IsFocus() const;
		
virtual void			SetView(BView* v);
		BView*			View() const;

virtual void			DrawFocusMark(BView*, BRect);
virtual void 			DrawLabel(BView*, BRect);
virtual void 			DrawTab(BView*, BRect, tab_position, bool full=true);

/*----- Private or reserved -----------------------------------------*/
private:
virtual	void			_ReservedTab1();
virtual	void			_ReservedTab2();
virtual	void			_ReservedTab3();
virtual	void			_ReservedTab4();
virtual	void			_ReservedTab5();
virtual	void			_ReservedTab6();
virtual	void			_ReservedTab7();
virtual	void			_ReservedTab8();
virtual	void			_ReservedTab9();
virtual	void			_ReservedTab10();
virtual	void			_ReservedTab11();
virtual	void			_ReservedTab12();

	BTab				&operator=(const BTab &);
		
	bool 				fEnabled;
	bool				fSelected;
	bool				fFocus;
	BView*				fView;
	uint32				_reserved[12];
};

/*----------------------------------------------------------------*/
/*----- BTabView class -------------------------------------------*/

class BTabView : public BView {
public:
						BTabView(BRect frame, const char *name,
							button_width width=B_WIDTH_AS_USUAL,
							uint32 resizingMode = B_FOLLOW_ALL,
							uint32 flags = B_FULL_UPDATE_ON_RESIZE |
								B_WILL_DRAW | B_NAVIGABLE_JUMP |
								B_FRAME_EVENTS | B_NAVIGABLE);
						~BTabView();
						
						BTabView(BMessage*);							
static	BArchivable*	Instantiate(BMessage*);
virtual	status_t		Archive(BMessage*, bool deep=true) const;
virtual status_t		Perform(perform_code d, void *arg);

virtual void 			WindowActivated(bool state);
virtual void 			AttachedToWindow();		
virtual	void			AllAttached();
virtual	void			AllDetached();
virtual	void			DetachedFromWindow();

virtual void 			MessageReceived(BMessage *msg);
virtual void 			FrameMoved(BPoint new_position);
virtual void			FrameResized(float w,float h);
virtual void 			KeyDown(const char * bytes, int32 n);
virtual void			MouseDown(BPoint);
virtual void			MouseUp(BPoint);
virtual void 			MouseMoved(BPoint pt, uint32 code, const BMessage *msg);
virtual	void			Pulse();

virtual	void 			Select(int32);
		int32			Selection() const;

virtual	void			MakeFocus(bool focusState = true);
virtual void			SetFocusTab(int32,bool);
		int32			FocusTab() const;
		
virtual void 			Draw(BRect);
virtual BRect			DrawTabs();
virtual void			DrawBox(BRect);
virtual BRect			TabFrame(int32) const;
				
virtual	void			SetFlags(uint32 flags);
virtual	void			SetResizingMode(uint32 mode);

virtual void 			GetPreferredSize( float *width, float *height);
virtual void 			ResizeToPreferred();

virtual BHandler		*ResolveSpecifier(BMessage *msg, int32 index,
						BMessage *specifier, int32 form, const char *property);
virtual	status_t		GetSupportedSuites(BMessage *data);
			
virtual	void 			AddTab(BView* v, BTab* tab=NULL);
virtual	BTab*			RemoveTab(int32) const;
virtual	BTab*			TabAt(int32) const;
		
virtual	void			SetTabWidth(button_width s);
		button_width	TabWidth() const;
		
virtual	void			SetTabHeight(float);
		float			TabHeight() const;		
		
/*----- Private or reserved -----------------------------------------*/
private:
		BView*			_ViewContainer() const;

virtual	void			_ReservedTabView1();
virtual	void			_ReservedTabView2();
virtual	void			_ReservedTabView3();
virtual	void			_ReservedTabView4();
virtual	void			_ReservedTabView5();
virtual	void			_ReservedTabView6();
virtual	void			_ReservedTabView7();
virtual	void			_ReservedTabView8();
virtual	void			_ReservedTabView9();
virtual	void			_ReservedTabView10();
virtual	void			_ReservedTabView11();
virtual	void			_ReservedTabView12();

						BTabView(const BTabView &);
		BTabView		&operator=(const BTabView &);
	
		BList*			fTabList;
		BView*			fViewContainer;
		button_width	fTabWidthSetting;
		float 			fTabWidth;
		float			fTabHeight;
		int32			fSelection;
		int32			fInitialSelection;
		int32			fFocus;	
		uint32			_reserved[12];

};

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/

#endif /* _TAB_VIEW_H */
