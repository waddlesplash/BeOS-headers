//******************************************************************************
//
//	File:		Control.h
//
//	Description:	base control view class interface
//
//	Copyright 1993-96, Be Incorporated
//
//******************************************************************************
 
#ifndef	_CONTROL_H
#define	_CONTROL_H

#ifndef _VIEW_H
#include "View.h"
#endif
#ifndef _MESSAGE_H
#include <Message.h>
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif
#ifndef _LOOPER_H
#include <Looper.h>
#endif

enum {
	B_CONTROL_OFF = 0,
	B_CONTROL_ON = 1
};

//------------------------------------------------------------------------------

class BWindow;

class BControl : public BView {
	B_DECLARE_CLASS_INFO(BView);

public:
					BControl(	BRect frame,
								const char *name,
								const char *label,
								BMessage *message,
								ulong resizeMask,
								ulong flags); 
virtual				~BControl();

virtual	void		AttachedToWindow();

virtual	void		SetLabel(const char *text);
		const char	*Label() const;
		
virtual	void		SetValue(long value);
		long		Value() const;

virtual void		SetEnabled(bool on);
		bool		IsEnabled() const;

virtual	void		SetMessage(BMessage *message);
		BMessage	*Message() const;
		ulong		Command() const;

virtual long		SetTarget(BHandler *target);
virtual long		SetTarget(BLooper *target, bool preferred);
		BHandler	*Target(BLooper **looper = NULL) const;

//-----------------------------------------------------------------------------

protected:
	void			Invoke();

//-----------------------------------------------------------------------------

private:
	BMessage		*fMessage;
	char			*fLabel;
	long			fValue;
	BHandler		*fTarget;
	BLooper			*fLooper;
	bool			fEnabled;
};

//------------------------------------------------------------------------------

#endif
