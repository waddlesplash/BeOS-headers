/*
	
	Menu.h
	
	Copyright 1994-97 Be, Inc. All Rights Reserved.
	
*/

#pragma once

#ifndef _MENU_H
#define _MENU_H

#include <InterfaceDefs.h>
#include <View.h>
#include <Looper.h>
#include <List.h>

class BMenuItem;
class BMenuBar;
class BMenuWindow;
extern "C" status_t _init_interface_kit_();

enum menu_layout {
	B_ITEMS_IN_ROW = 0,
	B_ITEMS_IN_COLUMN,
	B_ITEMS_IN_MATRIX
};

struct menu_info {
	float		font_size;
	font_family	f_family;
	font_style	f_style;
	rgb_color	background_color;
	int32		separator;
	bool		click_to_open;
	bool		triggers_always_shown;
};

status_t	set_menu_info(menu_info *info);
status_t	get_menu_info(menu_info *info);

class BMenu : public BView
{
public:

/* Public Interface for clients of this class */

						BMenu(	const char *title,
								menu_layout layout = B_ITEMS_IN_COLUMN);
						BMenu(const char *title, float width, float height);
virtual					~BMenu();

						BMenu(BMessage *data);
static	BMenu			*Instantiate(BMessage *data);
virtual	status_t		Archive(BMessage *data, bool deep = true) const;

virtual void			AttachedToWindow();
virtual void			DetachedFromWindow();

		bool			AddItem(BMenuItem *item);
		bool			AddItem(BMenuItem *item, int32 index);
		bool			AddItem(BMenuItem *item, BRect frame);
		bool			AddItem(BMenu *menu);
		bool			AddItem(BMenu *menu, int32 index);
		bool			AddItem(BMenu *menu, BRect frame);
		bool			AddSeparatorItem();
		bool			RemoveItem(BMenuItem *item);
		BMenuItem		*RemoveItem(int32 index);
		bool			RemoveItem(BMenu *menu);

		BMenuItem		*ItemAt(int32 index) const;
		BMenu			*SubmenuAt(int32 index) const;
		int32			CountItems() const;
		int32			IndexOf(BMenuItem *item) const;
		int32			IndexOf(BMenu *menu) const;
		BMenuItem		*FindItem(uint32 command) const;
		BMenuItem		*FindItem(const char *name) const;

virtual	status_t		SetTargetForItems(BHandler *target);
virtual	status_t		SetTargetForItems(BMessenger messenger);
virtual	void			SetEnabled(bool state);
virtual	void			SetRadioMode(bool state);
virtual	void			SetTriggersEnabled(bool state);
virtual void			SetMaxContentWidth(float max);

		bool			IsEnabled() const;	
		bool			IsRadioMode() const;
		bool			AreTriggersEnabled() const;
		float			MaxContentWidth() const;

		BMenuItem		*FindMarked();

		BMenu			*Supermenu() const;
		BMenuItem		*Superitem() const;

/* Public Interface for derived classes of the menu system */

virtual void			MessageReceived(BMessage *msg);
virtual	void			KeyDown(const char *bytes, int32 numBytes);
virtual void			Draw(BRect updateRect);
virtual void			GetPreferredSize(float *width, float *height);
virtual void			ResizeToPreferred();
virtual	void			FrameMoved(BPoint new_position);
virtual	void			FrameResized(float new_width, float new_height);
		void			InvalidateLayout();
	
virtual BHandler		*ResolveSpecifier(BMessage *msg,
										int32 index,
										BMessage *specifier,
										int32 form,
										const char *property);
virtual status_t		GetSupportedSuites(BMessage *data);

virtual status_t		Perform(uint32 d, void *arg);

// -------------------------------------------------------------//
// -------------------------------------------------------------//
protected:
				
					// special constructor for BMenuBar and
					// other subclasses of BMenu.
					BMenu(	BRect frame,
							const char *viewName,
							uint32 resizeMask,
							uint32 flags,
							menu_layout layout,
							bool resizeToFit);

virtual	BPoint		ScreenLocation();

		void		SetLabelFromMarked(bool on);
		bool		IsLabelFromMarked();

		void		SetItemMargins(	float left, 
									float top, 
									float right, 
									float bottom);
		void		GetItemMargins(	float *left, 
									float *top, 
									float *right, 
									float *bottom) const;

		menu_layout	Layout() const;

virtual	void		Show();
		void		Show(bool selectFirstItem);
		void		Hide();
		BMenuItem	*Track(	bool start_opened = FALSE,
							BRect *special_rect = NULL);

// -------------------------------------------------------------//
// -------------------------------------------------------------//
private:
friend BWindow;
friend BMenuBar;
friend BMenuItem;
friend status_t _init_interface_kit_();
friend status_t	set_menu_info(menu_info *);
friend status_t	get_menu_info(menu_info *);

virtual	void			_ReservedMenu1();
virtual	void			_ReservedMenu2();
virtual	void			_ReservedMenu3();
virtual	void			_ReservedMenu4();
virtual	void			_ReservedMenu5();
virtual	void			_ReservedMenu6();

		BMenu			&operator=(const BMenu &);

		void		InitData(BMessage *data = NULL);
		void		_show(bool selectFirstItem = FALSE);
		void		_hide();
		BMenuItem	*_track(int *action, long start = -1);
		void		RemoveItem(int32 index, BMenuItem *item);
		void		LayoutItems(int32 index);
		BRect		Bump(BRect current, BPoint extent, int32 index) const;
		BPoint		ItemLocInRect(BRect frame) const;
		BRect		CalcFrame(BPoint where, bool *scrollOn);
		bool		ScrollMenu(BRect bounds, BPoint loc, bool *fast);
		void		ScrollIntoView(BMenuItem *item);

		void		DrawItems(BRect updateRect);
		int			State(BMenuItem **item = NULL) const;
		void		InvokeItem(BMenuItem *item, bool now = FALSE);

		bool		OverSuper(BPoint loc);
		bool		OverSubmenu(BMenuItem *item, BPoint loc);
		BMenuWindow	*MenuWindow();
		void		DeleteMenuWindow();
		BMenuItem	*HitTestItems(BPoint where, BPoint slop = B_ORIGIN) const;
		BRect		Superbounds() const;
		void		CacheFontInfo();

		void		ItemMarked(BMenuItem *item);
		void		Install(BWindow *target);
		void		Uninstall();
		void		SelectItem(	BMenuItem *m,
								uint32 showSubmenu = 0,
								bool selectFirstItem = FALSE);
		BMenuItem	*CurrentSelection() const;
		bool		SelectNextItem(BMenuItem *item, bool forward);
		BMenuItem	*NextItem(BMenuItem *item, bool forward) const;
		bool		IsItemVisible(BMenuItem *item) const;
		void		SetIgnoreHidden(bool on);
		void		SetStickyMode(bool on);
		bool		IsStickyMode() const;
		void		CalcTriggers();
		const char	*ChooseTrigger(const char *title, BList *chars);
		void		UpdateWindowViewSize(bool upWind = TRUE);
		bool		IsStickyPrefOn();
		void		RedrawAfterSticky(BRect bounds);

static	menu_info	sMenuInfo;

		BMenuItem	*fChosenItem;
		BList		fItems;
		BRect		fPad;
		BMenuItem	*fSelected;
		BMenuWindow	*fCachedMenuWindow;	// tmp window where submenus live
		BMenu		*fSuper;		// the BMenu that brought up this menu
		BMenuItem	*fSuperitem;	// item in menu that bought up this menu
		BRect		fSuperbounds;	// should be in global coords
		float		fAscent;
		float		fDescent;
		float		fFontHeight;
		uint32		fState;
		menu_layout	fLayout;
		BRect		*fExtraRect;
		float		fMaxContentWidth;
		uint32		_reserved[4];

		char		fTrigger;
		bool		fResizeToFit;
		bool		fUseCachedMenuLayout;
		bool		fEnabled;
		bool		fDynamicName;
		bool		fRadioMode;
		bool		fTrackNewBounds;
		bool		fStickyMode;
		bool		fIgnoreHidden;
		bool		fTriggerEnabled;
		bool		fRedrawAfterSticky;
};

#endif
