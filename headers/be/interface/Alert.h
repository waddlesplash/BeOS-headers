/*******************************************************************************
**
**	File:		Alert.h
**
**	Description:	Alert class.
**
**	Copyright 1993-97, Be Incorporated
**
********************************************************************************/
 
#pragma once

#ifndef	_ALERT_H
#define	_ALERT_H

#include <Window.h>
#include <Button.h>
#include <TextView.h>
#include <Invoker.h>
#include <ClassInfo.h>

enum button_width {
	B_WIDTH_AS_USUAL,
	B_WIDTH_FROM_WIDEST,
	B_WIDTH_FROM_LABEL
};

enum alert_type {
	B_EMPTY_ALERT = 0,
	B_INFO_ALERT,
	B_IDEA_ALERT,
	B_WARNING_ALERT,
	B_STOP_ALERT
};

class BBitmap;

class BAlert : public BWindow
{
public:

					BAlert(	const char *title,
							const char *text,
							const char *button1,
							const char *button2 = NULL,
							const char *button3 = NULL,
							button_width width = B_WIDTH_AS_USUAL,
							alert_type type = B_INFO_ALERT);
					BAlert(BMessage *data);
virtual				~BAlert();
static	BAlert		*Instantiate(BMessage *data);
virtual	status_t	Archive(BMessage *data, bool deep = true) const;
	
		void		SetShortcut(int32 button_index, char key);
		char		Shortcut(int32 button_index) const;

		int32		Go();
		status_t	Go(BInvoker *invoker);

virtual	void		MessageReceived(BMessage *an_event);
virtual	void		FrameResized(float new_width, float new_height);
		BButton		*ButtonAt(int32 index) const;
		BTextView	*TextView() const;

virtual BHandler	*ResolveSpecifier(BMessage *msg,
									int32 index,
									BMessage *specifier,
									int32 form,
									const char *property);
virtual	status_t	GetSupportedSuites(BMessage *data);

virtual status_t	Perform(uint32 d, void *arg);

// ------------------------------------------------------------------

private:
friend class _BAlertFilter_;

virtual	void		_ReservedAlert1();
virtual	void		_ReservedAlert2();
virtual	void		_ReservedAlert3();

		void		InitObject(const char *text,
							const char *button1,
							const char *button2 = NULL,
							const char *button3 = NULL,
							button_width width = B_WIDTH_AS_USUAL,
							alert_type type = B_INFO_ALERT);
		BBitmap		*InitIcon();

		sem_id			fAlertSem;
		int32			fAlertVal;
		BButton			*fButtons[3];
		BTextView		*fTextView;
		char			fKeys[3];
		alert_type		fMsgType;
		button_width	fButtonWidth;
		BInvoker		*fInvoker;
		uint32			_reserved[4];
};

#endif

