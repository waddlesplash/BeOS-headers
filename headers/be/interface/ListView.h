/*******************************************************************************
**
**	File:		ListView.h
**
**	Description:	client list view class.
**
**	Copyright 1992-93, Be Incorporated
**
*******************************************************************************/
#ifndef _LIST_VIEW_H
#define _LIST_VIEW_H

#ifndef _VIEW_H
#include "View.h"
#endif
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif
#ifndef _LIST_H
#include <support/List.h>
#endif

class BListView : public BView
{
	DECLARE_CLASS_INFO(BView);

public:
					BListView(	BRect frame,
								const char *name,
								ulong resizeMask = FOLLOW_LEFT_TOP,
								ulong flags = WILL_DRAW | FRAME_EVENTS);
virtual				~BListView();
virtual	void		Draw(BRect updateRect);
virtual	void		MouseDown(BPoint where);
virtual	void		KeyDown(ulong aKey);
virtual	void		FrameResized(long newWidth, long newHeight);
		bool		AddItem(void *item);
		bool		AddItem(void *item, long atIndex);
		bool		AddList(BList *newItems);
		bool		AddList(BList *newItems, long atIndex);
		bool		RemoveItem(void *item);
		void		*RemoveItem(long index);

virtual	void		SetTarget(BWindow *target);
		void		SetSelectionMessage(ulong command);
virtual	void		SetSelectionMessage(BMessage *message);
		void		SetInvocationMessage(ulong command);
virtual	void		SetInvocationMessage(BMessage *message);

		BWindow		*Target() const;
		BMessage	*SelectionMessage() const;
		ulong		SelectionCommand() const;
		BMessage	*InvocationMessage() const;
		ulong		InvocationCommand() const;

		void		*ItemAt(long) const;
		long		IndexOf(void *item) const;
		void		*FirstItem() const;
		void		*LastItem() const;
		bool		HasItem(void *) const;
		long		CountItems() const;
		void		MakeEmpty();
		bool		IsEmpty() const;
		void		DoForEach(bool (*func)(void *));
		void		DoForEach(bool (*func)(void *, void *), void *);
		void		*Items() const;
		void		InvalidateItem(long index);

virtual	void		Select(long index);
		void		Select(void *item);
		bool		IsItemSelected(void *item) const;
		void		*CurrentSelection() const;

virtual void		Invoke(long index);
		void		Invoke(void *item);

		void		SortItems(int (*cmp)(const void *, const void *));
	
// ------------------------------------------------------------------

protected:

virtual	void		DrawItem(BRect updateRect, void *item);
virtual	void		HighlightItem(bool on, void *item);
virtual long		ItemHeight();
		BRect		ItemFrame(long index);


// ------------------------------------------------------------------

private:
		void		FixupScrollBar();
		void		InvalidateFrom(long y);
		BScrollBar	*ScrollBar();
		void		Post(BMessage *msg, long index);

		BList		fList;
		void		*fSelected;
		long		fIndex;
		ulong		fClickTime;
		BScrollBar	*fScroll;
		long		fBaselineOffset;
		BMessage	*fSelectMessage;
		BMessage	*fInvokeMessage;
		BWindow		*fTarget;
};

inline void *BListView::Items() const
	{ return fList.Items(); }

inline bool BListView::IsItemSelected(void *item) const
	{ return(fSelected == item); }

inline void *BListView::CurrentSelection() const
	{ return(fSelected); }

inline BWindow *BListView::Target() const
	{ return(fTarget); }

#endif
