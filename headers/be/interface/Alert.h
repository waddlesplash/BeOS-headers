/*******************************************************************************
**
**	File:		Alert.h
**
**	Description:	Alert class.
**
**	Copyright 1993-96, Be Incorporated
**
********************************************************************************/
 
#ifndef	_ALERT_H
#define	_ALERT_H

#ifndef _WINDOW_H
#include "Window.h"
#endif
#ifndef _BUTTON_H
#include "Button.h"
#endif
#ifndef _TEXT_VIEW_H
#include "TextView.h"
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

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


class BAlert : public BWindow
{
	B_DECLARE_CLASS_INFO(BWindow);
public:

					BAlert(	const char *title,
							const char *text,
							const char *button1,
							const char *button2 = NULL,
							const char *button3 = NULL,
							button_width width = B_WIDTH_AS_USUAL,
							alert_type type = B_INFO_ALERT);
	
		void		SetShortcut(long button_index, char key);

		long		Go();
virtual	void		MessageReceived(BMessage *an_event);
virtual	bool		FilterKeyDown(ulong *aKey, BView **target);	
virtual	void		FrameResized(float new_width, float new_height);
		BButton		*ButtonAt(long index) const;
		BTextView	*TextView() const;

// ------------------------------------------------------------------

private:
	long			fAlertSem;
	long			fAlertVal;
	BButton			*fButtons[3];
	BTextView		*fTextView;
	char			fKeys[3];
	int				fMsgType;
};

inline BButton *BAlert::ButtonAt(long index) const
	{ return fButtons[index]; };

inline BTextView *BAlert::TextView() const
	{ return fTextView; };

#endif

