//******************************************************************************
//
//	File:		menubar.h
//
//	Description:	menubar view class.
//
//	Copyright 1992, Be Incorporated
//
//******************************************************************************

#ifndef	_MENUBAR_H
#define	_MENUBAR_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef _VIEW_H
#include "View.h"
#endif
#ifndef _WINDOW_H
#include "Window.h"
#endif
#ifndef	_OBJECT_H
#include <support/Object.h>
#endif
#ifndef _LIST_H
#include <support/List.h>
#endif
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

class	TMenuBar : public BView {
	DECLARE_CLASS_INFO(BView);

public:
				TMenuBar(const char *name, BRect view_bound, long view_type);
virtual			~TMenuBar();
		void	SetLabel(long item_code, const char *name);
		void	set_enable(long item_code, char enable);
		void	set_key(long item_code, char key);
		void	set_mark(long item_code, char mark);

// ----------------------------------------------------------------

private:

friend class TMenu;

		void	AddMenu(TMenu*);
		BList*	fMenuList;
};

inline void	TMenuBar::AddMenu(TMenu* m)	{ fMenuList->AddItem(m); }

//------------------------------------------------------------------------------

class	TMenu :	BObject {
	DECLARE_CLASS_INFO(BObject);

public:
				TMenu(const char *name, TMenuBar *menu_bar);
virtual			~TMenu();
		void	add_item(	const char *name,
							long message,
							char key = 0,
							char enable = 1);

// ----------------------------------------------------------------

private:
		char		*menu_name;
		long		server_token;
		long		client_token;
		TMenuBar	*owner;
};

//------------------------------------------------------------------------------

#endif
