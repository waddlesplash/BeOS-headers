//******************************************************************************
//
//	File:		menubar.h
//
//	Description:	menubar view class.
//
//	Written by:	Benoit Schillings
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
#include <sys/Object.h>
#endif


class	TMenuBar : public BView {
public:
			TMenuBar(char *name, BRect *view_bound, long view_type);
virtual			~TMenuBar();
	void		SetLabel(long item_code, char *name);
	void		set_enable(long item_code, char enable);
	void		set_key(long item_code, char key);
	void		set_mark(long item_code, char mark);
};

//------------------------------------------------------------------------------

class	TMenu :	BObject {
		char		*menu_name;
		long		server_token;
		long		client_token;
		TMenuBar	*owner;
		
public:
			TMenu(char *name, TMenuBar *menu_bar);
virtual			~TMenu();
		void	add_item(char *name, long message, char key = 0, char enable = 1);
		void	remove_menu();
};

//------------------------------------------------------------------------------

#endif
