/*
	
	PopUpMenu.h
	
	Copyright 1994-97 Be, Inc. All Rights Reserved.
	
*/

#pragma once

#ifndef _POP_UP_MENU_H
#define _POP_UP_MENU_H

#include <Menu.h>

class BPopUpMenu : public BMenu
{
public:
					BPopUpMenu(	const char *title,
								bool radioMode = TRUE,
								bool autoRename = TRUE,
								menu_layout layout = B_ITEMS_IN_COLUMN
								);
					BPopUpMenu(BMessage *data);
virtual				~BPopUpMenu();
virtual status_t	Archive(BMessage *data, bool deep = true) const;
static	BPopUpMenu	*Instantiate(BMessage *data);

		BMenuItem	*Go(BPoint where,
						bool delivers_message = FALSE,
						bool open_anyway = FALSE,
						bool async = FALSE);
		BMenuItem	*Go(BPoint where,
						bool delivers_message,
						bool open_anyway,
						BRect click_to_open,
						bool async = FALSE);

virtual void		MessageReceived(BMessage *msg);
virtual	void		MouseDown(BPoint pt);
virtual	void		MouseUp(BPoint pt);
virtual	void		MouseMoved(BPoint pt, uint32 code, const BMessage *msg);
virtual	void		AttachedToWindow();
virtual	void		DetachedFromWindow();
virtual	void		FrameMoved(BPoint new_position);
virtual	void		FrameResized(float new_width, float new_height);

virtual BHandler	*ResolveSpecifier(BMessage *msg,
									int32 index,
									BMessage *specifier,
									int32 form,
									const char *property);
virtual status_t	GetSupportedSuites(BMessage *data);

virtual status_t	Perform(uint32 d, void *arg);

protected:
virtual	BPoint		ScreenLocation();

virtual	void		_ReservedPopUpMenu1();
virtual	void		_ReservedPopUpMenu2();
virtual	void		_ReservedPopUpMenu3();

		BPopUpMenu	&operator=(const BPopUpMenu &);

private:
		BMenuItem	*_go(	BPoint where,
							bool autoInvoke,
							bool start_opened,
							BRect *special_rect,
							bool async);
static	int32		entry(void *);
		BMenuItem	*start_track(BPoint where,
								bool autoInvoke,
								bool start_opened,
								BRect *special_rect);

		BPoint		fWhere;
		bool		fUseWhere;
		thread_id	fTrackThread;
		uint32		_reserved[3];
};

#endif
