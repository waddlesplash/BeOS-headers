/*
	
	Menu.h
	
	Copyright 1994 Be, Inc. All Rights Reserved.
	
*/

#ifndef _MENU_H
#define _MENU_H

#ifndef _INTERFACE_DEFS_H
#include <interface/InterfaceDefs.h>
#endif
#ifndef _VIEW_H
#include <interface/View.h>
#endif
#ifndef _LIST_H
#include <support/List.h>
#endif

class BMenuItem;
class BMenuBar;
class BMenuWindow;

enum menu_layout {
	ITEMS_IN_ROW = 0,
	ITEMS_IN_COLUMN,
	ITEMS_IN_MATRIX
};

class BMenu : public BView
{
		DECLARE_CLASS_INFO(BView);
public:

/* Public Interface for clients of this class */

						BMenu(	const char *title,
								menu_layout layout = ITEMS_IN_COLUMN);
						BMenu(const char *title, long width, long height);
virtual					~BMenu();

virtual void			AttachedToWindow();

		void			AddItem(BMenuItem *item);
		void			AddItem(BMenuItem *item, long index);
		void			AddItem(BMenuItem *item, BRect frame);
		void			AddItem(BMenu *menu);
		void			AddItem(BMenu *menu, long index);
		void			AddItem(BMenu *menu, BRect frame);
		void			AddSeparatorItem();
		void			RemoveItem(BMenuItem *item);
		void			RemoveItem(long index);
		void			RemoveItem(BMenu *menu);

		BMenuItem		*ItemAt(long index) const;
		BMenu			*SubmenuAt(long index) const;
		long			CountItems() const;
		long			IndexOf(BMenuItem *item) const;
		long			IndexOf(BMenu *menu) const;
		BMenuItem		*FindItem(ulong command) const;
		BMenuItem		*FindItem(const char *name) const;

virtual	void			SetTitle(const char *title);
virtual	void			SetTarget(BWindow *target);
virtual	void			SetEnabled(bool state);
virtual	void			SetRadioMode(bool state);
virtual void			SetTrigger(char ch);

		const char		*Title() const;
		BWindow			*Target() const;
		bool			IsEnabled() const;	
		bool			IsRadioMode() const;
		char			Trigger() const;
		
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

		void		SetTitleFromMarked(bool on);
		bool		IsTitleFromMarked();

		menu_layout	Layout() const;

		/*
		These 3 functions are protected, so that subclasses can
		initiated menu tracking. They can't customize the way
		tracking works. But the can "initiate" it.
		*/
		void		Show(bool selectFirstItem = FALSE);
		void		Hide();
		BMenuItem	*Track();

// -------------------------------------------------------------//
// -------------------------------------------------------------//
private:
friend BWindow;		// it calls InvokeItem for menu shortcuts
friend BMenuBar;
friend BMenuItem;

		void		_show(bool selectFirstItem = FALSE);
		void		_hide();
		BMenuItem	*_track(int *action, long start = -1);
		void		RemoveItem(long index, BMenuItem *item);
		void		LayoutItems(long index);
		BRect		Bump(BRect current, BPoint extent, int index) const;
		BPoint		ItemLocInRect(BRect frame) const;
		BRect		CalcFrame(BPoint where, bool *scrollOn);
		bool		ScrollMenu(BRect bounds, BPoint loc);
		void		ScrollIntoView(BMenuItem *item);

		void		DrawItems();
		int			State(BMenuItem **item = NULL) const;
		void		InvokeItem(BMenuItem *item, bool now = FALSE);

		bool		OverSuper(BPoint loc);
		bool		OverSubmenu(BMenuItem *item, BPoint loc);
		BMenuWindow	*MenuWindow();
		void		DeleteMenuWindow();
		BMenuItem	*HitTestItems(BPoint where, BPoint slop = ORIGIN) const;
		BRect		Superbounds() const;
		void		SetPad(BRect pad);

		void		ItemMarked(BMenuItem *item);
		void		Install(BWindow *target, BMenu *super, BMenuItem *sitem);
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

		char		*fTitle;
		BMenuItem	*fChosenItem;
		BList		fItems;
		BRect		fPad;
		BMenuItem	*fSelected;
		BWindow		*fTarget;
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
};

#endif
