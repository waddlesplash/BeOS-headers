//******************************************************************************
//
//	File:		Box.h
//
//	Description:	client framed view class.
//
//	Copyright 1993-94, Be Incorporated
//
//******************************************************************************
#ifndef _BOX_H
#define _BOX_H

#ifndef _CONTROL_H
#include "Control.h"
#endif

#ifndef _CLASS_INFO_H
#include "ClassInfo.h"
#endif

class BBox : public BView
{
	DECLARE_CLASS_INFO(BView);

public:
					BBox(	BRect bounds,
							const char *name = NULL,
							ulong resizeFlags = FOLLOW_LEFT_TOP,
							ulong flags = WILL_DRAW | FULL_UPDATE_ON_RESIZE);
virtual 			~BBox(void);

		const char	*Label() const;
		void		SetLabel(const char *label);
virtual	void		Draw(BRect bounds);
virtual	void		AttachedToWindow();

virtual long		ResourceDataLength() const;
virtual void		GetResourceData(void *buf) const;
virtual void		SetResourceData(void *buf, long len);

// ----------------------------------------------------------------

private:
		char		*fLabel;
};

#endif
