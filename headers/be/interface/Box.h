//******************************************************************************
//
//	File:		Box.h
//
//	Description:	client framed view class.
//
//	Copyright 1993-96, Be Incorporated
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
	B_DECLARE_CLASS_INFO(BView);

public:
					BBox(	BRect bounds,
							const char *name = NULL,
							ulong resizeFlags = B_FOLLOW_LEFT_TOP,
							ulong flags = B_WILL_DRAW);
virtual 			~BBox(void);

		const char	*Label() const;
		void		SetLabel(const char *label);
virtual	void		Draw(BRect bounds);
virtual	void		AttachedToWindow();

// ----------------------------------------------------------------

private:
		char		*fLabel;
};

#endif
