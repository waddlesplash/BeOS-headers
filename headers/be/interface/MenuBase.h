/*
	
	MenuBase.h
	
	Copyright 1994 Be, Inc. All Rights Reserved.
	
*/

#ifndef _MENU_BASE_H
#define _MENU_BASE_H

#ifndef _INTERFACE_DEFS_H
#include <interface/InterfaceDefs.h>
#endif
#ifndef _VIEW_H
#include <interface/View.h>
#endif
#ifndef _LIST_H
#include <support/List.h>
#endif

class BView;
class BMenuItem;
class BMenu;
class BMenuWindow;
class BMenuBar;

enum menu_layout {
	HORIZONTAL_MENU = 0,
	HORIZONTAL_MENU_BAR = HORIZONTAL_MENU, 
	VERTICAL_MENU = 1,
	VERTICAL_MENU_BAR = VERTICAL_MENU,
	CUSTOM_MENU,
	CUSTOM_MENU_BAR = CUSTOM_MENU
};

enum menu_tracking {
	NOW_TRACKING = 0,
	DONE_TRACKING,
	SELECT_NEXT,
	SELECT_PREV
};

class BMenuBase : public BView
{
		DECLARE_CLASS_INFO(BView);

public:
		// ??? temporarily make this public so that Steve can play with
		// spacing of menus and menu items.
		void		SetPad(BRect pad);

virtual	void		Invoke(BMenuItem *item, bool now = FALSE);

protected:
					BMenuBase(	BRect frame,
								const char *viewName,
								ulong resizeMask,
								ulong flags,
								menu_layout layout,
								bool resizeToFit);
virtual				~BMenuBase();

		void		AddItem(BMenuItem *item, long index);
		void		AddItem(BMenuItem *item, BRect location);
		void		RemoveItem(BMenuItem *item);
		void		RemoveItem(long index);
		
virtual void		AttachedToWindow();

		long		CountItems() const;
		BMenuItem	*ItemAt(long index) const;
		long		IndexOf(BMenu *menu) const;
		long		IndexOf(BMenuItem *item) const;
		BMenuItem	*FindItem(ulong command) const;
		BMenuItem	*FindItem(const char *name) const;
		BMenuItem	*NextItem(BMenuItem *item, bool forward) const;
		
		BMenuItem	*HitTestItems(BPoint where, BPoint slop = ORIGIN) const;
		void		DrawItems();
virtual	void		Draw(BRect updateRect);
		
		void		InvalidateMenuLayout();

virtual	void		Show() = 0;
virtual	void		Hide() = 0;
virtual	BMenuItem	*Track(	menu_tracking *action,
							bool *stickyMode,
							long startIndex) = 0;
		
		void		SelectItem(BMenuItem *m);
		BMenuItem	*SelectedItem() const;
		void		SelectNextItem(BMenuItem *item, bool forward);

		bool		OverParent(BPoint loc);
		bool		OverSubMenu(BMenuItem *item, BPoint loc);
		menu_layout	Layout() const;
		BWindow		*Target() const;
		
		BMenuWindow	*MenuWindow();
		void		DeleteMenuWindow();

virtual	void		SetEnabled(bool state);
virtual	bool		IsEnabled() const;
		
		// ??? these 3 might really belong in BMenu class.
		BMenuBase	*ParentBase() const;
		BMenuItem	*ParentItem() const;
		BRect		ParentBounds() const;

		void		Install(BWindow *target,
							BMenuBase *parentBase,
							BMenuItem *parentItem);
		void		Uninstall();
private:
friend BMenuItem;
friend BMenuBar;

		void		LayoutItems(long index);
		BRect		Bump(BRect current, BPoint extent, int index) const;
		BPoint		ItemLocInRect(BRect bounds) const;
		void		RemoveItem(long index, BMenuItem *item);
		
		BList		fItems;
		menu_layout	fLayout;
		BRect		fPad;
		bool		fResizeToFit;
		bool		fUseCachedMenuLayout;
		bool		fEnabled;
		BMenuItem	*fSelected;
		BWindow		*fTarget;
		BMenuWindow	*fCachedMenuWindow;	// tmp window where submenus live

		// ??? These 3 might really belong in BMenu class
		BMenuBase	*fParentBase;	// the BMenuBase that brought up this menu
		BMenuItem	*fParentItem;	// the item in the menu that bought up this menu
		BRect		fParentBounds;	// should be in global coords
};

inline menu_layout BMenuBase::Layout() const
	{ return fLayout; };

#endif
