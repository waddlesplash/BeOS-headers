/*
	
	MenuItem.h
	
	Copyright 1994-96 Be, Inc. All Rights Reserved.
	
*/

#ifndef _MENU_ITEM_H
#define _MENU_ITEM_H

#ifndef _INTERFACE_DEFS_H
#include <InterfaceDefs.h>
#endif
#ifndef _OBJECT_H
#include <Object.h>
#endif
#ifndef _MESSAGE_H
#include <Message.h>
#endif
#ifndef _LOOPER_H
#include <Looper.h>
#endif
#ifndef _MENU_H
#include "Menu.h"
#endif

class BWindow;
class BView;
class BMenu;
class BPopUpMenu;
class BMenuBar;

class BMenuItem : public BObject
{
		B_DECLARE_CLASS_INFO(BObject);
public:

/* Public Interface for clients of this class */

						BMenuItem(	const char *label,
									BMessage *message,
									char shortcut = 0,
									ulong modifiers = 0);
						BMenuItem(BMenu *menu);
virtual					~BMenuItem();
	
virtual	void			SetLabel(const char *name);
virtual	long			SetTarget(BHandler *target);
virtual long			SetTarget(BLooper *target, bool preferred);
virtual	void			SetEnabled(bool state);
virtual	void			SetMarked(bool state);
virtual void			SetMessage(BMessage *message);
virtual void			SetTrigger(char ch);

		const char		*Label() const;
		BHandler		*Target(BLooper **looper = NULL) const;
		bool			IsEnabled() const;
		bool			IsMarked() const;
		ulong			Command() const;
		BMessage		*Message() const;
		char			Trigger() const;
		
		BMenu			*Submenu() const;
		char			Shortcut(ulong *modifiers = NULL) const;
		BMenu			*Menu() const;
		BRect			Frame() const;

protected:

virtual	void			GetContentSize(float *width, float *height);
virtual	void			DrawContent();
virtual	void			Draw();
virtual	void			Highlight(bool on);
		bool			IsSelected() const;
		BPoint			ContentLocation() const;

private:
friend	BMenu;
friend	BPopUpMenu;
friend	BMenuBar;

		void		Invoke();
		void		Install(BWindow *window);
		void		Uninstall();
		void		SetSuper(BMenu *super);
		void		Select(bool on);
		bool		IsSelected();
		void		CalcBaseline();
		void		DrawMarkSymbol();
		void		DrawShortcutSymbol();
		void		DrawSubmenuSymbol();
		void		SetSysTrigger(char ch);
		
		char		*fLabel;
		BMessage	*fMessage;
		BMenu		*fSubmenu;
		BWindow		*fWindow;
		BHandler	*fTarget;
		BLooper		*fLooper;
		BMenu		*fSuper;
		BRect		fBounds;		// in coord system of Super menu view
		ulong		fModifiers;
		float		fAscent;
		float		fDescent;
		float		fFontHeight;
		short		fTriggerIndex;
		char		fUserTrigger;
		char		fSysTrigger;
		char		fShortcutChar;
		bool		fMark;
		bool		fEnabled;
		bool		fSelected;
};

class BSeparatorItem : public BMenuItem
{
	B_DECLARE_CLASS_INFO(BMenuItem);
public:
				BSeparatorItem();
virtual			~BSeparatorItem();
virtual	void	SetEnabled(bool state);

protected:

virtual	void	GetContentSize(float *width, float *height);
virtual	void	Draw();

};

#endif
