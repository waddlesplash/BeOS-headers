//******************************************************************************
//
//	File:		Control.h
//
//	Description:	base control view class interface
//
//	Copyright 1993, Be Incorporated
//
//******************************************************************************
 
#ifndef	_CONTROL_H
#define	_CONTROL_H

#ifndef _VIEW_H
#include "View.h"
#endif
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BControl : public BView {
	DECLARE_CLASS_INFO(BView);

public:
					BControl(	BRect frame,
								const char *name,
								const char *label,
								ulong command,
								ulong resizeMask,
								ulong flags); 
virtual				~BControl();

virtual	void		AttachedToWindow();

		void		SetLabel(const char *text);
		const char	*Label() const;
		
		void		SetValue(long value);
		long		Value() const;
		void		SetCommand(ulong command);
		ulong		Command() const;
virtual	void		ValueChanged(long newValue);
virtual long		ResourceDataLength() const;
virtual void		GetResourceData(void *buf) const;
virtual void		SetResourceData(void *buf, long len);

//------------------------------------------------------------------------------

private:
	ulong		fCommand;
	char		*fLabel;
	long		fValue;
};

inline ulong		BControl::Command() const { return(fCommand); }

//------------------------------------------------------------------------------

#endif
