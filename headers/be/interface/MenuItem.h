/*
	
	MenuItem.h
	
	Copyright 1994 Be, Inc. All Rights Reserved.
	
*/

#ifndef _MENU_ITEM_H
#define _MENU_ITEM_H

#ifndef _INTERFACE_DEFS_H
#include <interface/InterfaceDefs.h>
#endif
#ifndef _OBJECT_H
#include <support/Object.h>
#endif

class BWindow;
class BMenu;
class BMenuBar;
class BMessage;

class BMenuItem : public BObject
{
		DECLARE_CLASS_INFO(BObject);
public:

/* Public Interface for clients of this class */

						BMenuItem(	const char *label,
									ulong command,
									char shortcut = 0,
									ulong modifiers = 0);
						BMenuItem(	const char *label,
									BMessage *msg,
									char shortcut = 0,
									ulong modifiers = 0);
						BMenuItem(BMenu *menu);
virtual					~BMenuItem();
	
virtual	void			SetLabel(const char *name);
virtual	void			SetTarget(BWindow *target);
virtual	void			SetEnabled(bool state);
virtual	void			SetMarked(bool state);
		void			SetMessage(ulong command);
virtual void			SetMessage(BMessage *message);
virtual void			SetTrigger(char ch);

		const char		*Label() const;
		BWindow			*Target() const;
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

virtual	void			GetContentSize(long *width, long *height);
virtual	void			DrawContent();
virtual	void			Draw();
virtual	void			Highlight(bool on);
		bool			IsSelected() const;
		BPoint			ContentLocation() const;

private:
friend	BMenu;
friend	BMenuBar;

		void		Invoke();
		void		Install(BWindow *target, BMenu *super);
		void		Uninstall();
		void		Select(bool on);
		bool		IsSelected();
		void		CalcBaseline();
		void		DrawMarkSymbol();
		void		DrawShortcutSymbol();
		void		DrawSubmenuSymbol();
		void		SetLocalTarget(BWindow *target);
		void		SetSysTrigger(char ch);
		
		char		*fLabel;
		BMessage	*fMessage;
		BMenu		*fSubmenu;
		BWindow		*fTarget;
		BMenu		*fSuper;
		BRect		fBounds;		// in coord system of Super menu view
		ulong		fModifiers;
		short		fOffset;
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
	DECLARE_CLASS_INFO(BMenuItem);
public:
				BSeparatorItem();
virtual			~BSeparatorItem();
virtual	void	SetEnabled(bool state);

protected:

virtual	void	GetContentSize(long *width, long *height);
virtual	void	Draw();

};

#endif
