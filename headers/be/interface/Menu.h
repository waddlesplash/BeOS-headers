/*
	
	Menu.h
	
	Copyright 1994-96 Be, Inc. All Rights Reserved.
	
*/

#ifndef _MENU_H
#define _MENU_H

#ifndef _INTERFACE_DEFS_H
#include <InterfaceDefs.h>
#endif
#ifndef _VIEW_H
#include <View.h>
#endif
#ifndef _LOOPER_H
#include <Looper.h>
#endif
#ifndef _LIST_H
#include <List.h>
#endif

class BMenuItem;
class BMenuBar;
class BMenuWindow;

enum menu_layout {
	B_ITEMS_IN_ROW = 0,
	B_ITEMS_IN_COLUMN,
	B_ITEMS_IN_MATRIX
};

class BMenu : public BView
{
		B_DECLARE_CLASS_INFO(BView);
public:

/* Public Interface for clients of this class */

						BMenu(	const char *title,
								menu_layout layout = B_ITEMS_IN_COLUMN);
						BMenu(const char *title, float width, float height);
virtual					~BMenu();

virtual void			AttachedToWindow();

		bool			AddItem(BMenuItem *item);
		bool			AddItem(BMenuItem *item, long index);
		bool			AddItem(BMenuItem *item, BRect frame);
		bool			AddItem(BMenu *menu);
		bool			AddItem(BMenu *menu, long index);
		bool			AddItem(BMenu *menu, BRect frame);
		bool			AddSeparatorItem();
		bool			RemoveItem(BMenuItem *item);
		BMenuItem		*RemoveItem(long index);
		bool			RemoveItem(BMenu *menu);

		BMenuItem		*ItemAt(long index) const;
		BMenu			*SubmenuAt(long index) const;
		long			CountItems() const;
		long			IndexOf(BMenuItem *item) const;
		long			IndexOf(BMenu *menu) const;
		BMenuItem		*FindItem(ulong command) const;
		BMenuItem		*FindItem(const char *name) const;

virtual	long			SetTargetForItems(BHandler *target);
virtual	void			SetEnabled(bool state);
virtual	void			SetRadioMode(bool state);
virtual	void			SetTriggersEnabled(bool state);

		bool			IsEnabled() const;	
		bool			IsRadioMode() const;
		bool			AreTriggersEnabled() const;
		
		BMenuItem		*FindMarked();

	// used to "walk" around the menu hierarchy.
		BMenu			*Supermenu() const;
		BMenuItem		*Superitem() const;

/* Public Interface for derived classes of the menu system */

virtual	void			KeyDown(ulong key);
virtual void			Draw(BRect updateRect);
		
	// Need this function in order to "dirty" a menu layout in
	// order to force and relayout
		void			InvalidateLayout();
	
// -------------------------------------------------------------//
// -------------------------------------------------------------//
protected:
				
					// special constructor for BMenuBar and
					// other subclasses of BMenu.
					BMenu(	BRect frame,
							const char *viewName,
							ulong resizeMask,
							ulong flags,
							menu_layout layout,
							bool resizeToFit);

virtual	BPoint		ScreenLocation();

		void		SetLabelFromMarked(bool on);
		bool		IsLabelFromMarked();

		menu_layout	Layout() const;

virtual	void		Show();
		void		Show(bool selectFirstItem);
		void		Hide();
		BMenuItem	*Track();

// -------------------------------------------------------------//
// -------------------------------------------------------------//
private:
friend BWindow;		// it calls InvokeItem for menu shortcuts
friend BMenuBar;
friend BMenuItem;

		void		SetPad(BRect pad);
		void		_show(bool selectFirstItem = FALSE);
		void		_hide();
		BMenuItem	*_track(int *action, long start = -1);
		void		RemoveItem(long index, BMenuItem *item);
		void		LayoutItems(long index);
		BRect		Bump(BRect current, BPoint extent, int index) const;
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

		void		ItemMarked(BMenuItem *item);
		void		Install(BWindow *target);
		void		Uninstall();
		void		SelectItem(	BMenuItem *m,
								int showSubmenu = 0,
								bool selectFirstItem = FALSE);
		BMenuItem	*CurrentSelection() const;
		void		SelectNextItem(BMenuItem *item, bool forward);
		BMenuItem	*NextItem(BMenuItem *item, bool forward) const;
		bool		IsItemVisible(BMenuItem *item) const;
		void		SetIgnoreHidden(bool on);
		void		SetStickyMode(bool on);
		bool		IsStickyMode() const;
		void		CalcTriggers();
		const char	*ChooseTrigger(const char *title, BList *chars);
		void		UpdateWindowViewSize(bool upWind = TRUE);

		BMenuItem	*fChosenItem;
		BList		fItems;
		BRect		fPad;
		BMenuItem	*fSelected;
		BMenuWindow	*fCachedMenuWindow;	// tmp window where submenus live
		BMenu		*fSuper;		// the BMenu that brought up this menu
		BMenuItem	*fSuperitem;	// item in menu that bought up this menu
		BRect		fSuperbounds;	// should be in global coords
		int			fState;
		menu_layout	fLayout;
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
};

#endif
