//******************************************************************************
//
//	File:		Control.h
//
//	Description:	base control view class interface
//
//	Written by:	Eric Knight
//
//	Copyright 1993, Be Incorporated
//
//******************************************************************************
 
#ifndef	_CONTROL_H
#define	_CONTROL_H

#ifndef _VIEW_H
#include "View.h"
#endif

//------------------------------------------------------------------------------

class BControl : public BView {
public:
			BControl(BRect *frame, char *name, char *label, 
				 long command, ulong resizeMask, ulong flags); 
virtual			~BControl();
virtual	char		*ClassName();
virtual	void		AttachedToWindow();

	void		SetLabel(char *text);
	char*		Label();
	
	void		SetValue(long value);
	long		Value();
	void		SetCommand(long command);
	long		Command();
virtual	void		ValueChanged(long newValue);
virtual long		ResourceDataLength();
virtual void		GetResourceData(void *buf);
virtual void		SetResourceData(void *buf, long len);

//------------------------------------------------------------------------------

private:
	long		fCommand;
	char		*fLabel;
	long		fValue;
};

inline long		BControl::Command() { return(fCommand); };
inline char		*BControl::ClassName() { return("BControl"); };

//------------------------------------------------------------------------------

#endif
