/*******************************************************************************
**
**	File:		Alert.h
**
**	Description:	Alert class.
**
**	Copyright 1993, Be Incorporated
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
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

class BAlert : public BWindow
{
	DECLARE_CLASS_INFO(BWindow);
public:
	
		void BAlert(const char *title,
					const char *text,
					const char *b1,
					const char *b2 = NULL,
					const char *b3 = NULL);
		
		void		SetShortcut(const char *button, char key);

		long		Run();
virtual	bool		CloseRequested(bool quitting = FALSE);	
virtual	void		MessageReceived(BMessage *an_event);
virtual	bool		FilterKeyDown(ulong *aKey, BView **target);	

// ------------------------------------------------------------------

private:
	long			alertSem;
	long			runSem;
	long			alertVal;
	BButton			*buttons[3];
	char			keys[3];
};

#endif

