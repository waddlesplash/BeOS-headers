/*
	
	Copyright 1994-96 Be, Inc. All Rights Reserved.
	
*/

#ifndef _MENU_FIELD_H
#define _MENU_FIELD_H

#ifndef _MENU_H
#include <Menu.h>
#endif
#ifndef _MENU_BAR_H
#include <MenuBar.h>
#endif

class BMenuField : public BView
{
public:
						BMenuField(	BRect frame,
									const char *name,
									const char *label,
									BMenu *menu,
									ulong resize = B_FOLLOW_LEFT | B_FOLLOW_TOP,
									ulong flags = B_WILL_DRAW | B_NAVIGABLE); 
virtual					~BMenuField();

virtual	void			Draw(BRect update);
virtual	void			AttachedToWindow();
virtual	void			AllAttached();
virtual	void			MouseDown(BPoint where);
virtual	void			KeyDown(ulong key);
virtual	void			MakeFocus(bool state);

		BMenu			*Menu() const;
		BMenuBar		*MenuBar() const;

virtual	void			SetLabel(const char *label);
		const char		*Label() const;
		
virtual void			SetEnabled(bool on);
		bool			IsEnabled() const;

virtual	void			SetAlignment(alignment label);
		alignment		Alignment() const;
virtual	void			SetDivider(float dividing_line);
		float			Divider() const;

private:
friend class _BMCMenuBar_;

		void			DrawLabel(BRect bounds);
static	long			MenuTask(void *arg);

		char			*fLabel;
		BMenu			*fMenu;
		BMenuBar		*fMenuBar;
		alignment		fAlign;
		float			fDivider;
		float			fStringWidth;
		bool			fEnabled;
		bool			fSelected;
		bool			fTransition;
		thread_id		fMenuTaskID;
		BMessageFilter	*fKeyDownFilter;
		BMessageFilter	*fMouseDownFilter;
};

#endif
