/*******************************************************************************
**
**	File:		ListView.h
**
**	Description:	client list view class.
**
**	Copyright 1992-96, Be Incorporated
**
*******************************************************************************/
#ifndef _LIST_VIEW_H
#define _LIST_VIEW_H

#ifndef _VIEW_H
#include "View.h"
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif
#ifndef _LOOPER_H
#include <Looper.h>
#endif
#ifndef _LIST_H
#include <List.h>
#endif


class BListView : public BView
{

public:
					BListView(	BRect frame,
								const char *name,
								ulong resizeMask = B_FOLLOW_LEFT | B_FOLLOW_TOP,
								ulong flags = B_WILL_DRAW | B_FRAME_EVENTS |
												B_NAVIGABLE);
virtual				~BListView();
virtual	void		Draw(BRect updateRect);
virtual	void		MouseDown(BPoint where);
virtual	void		KeyDown(ulong aKey);
virtual	void		MakeFocus(bool state = TRUE);
virtual	void		FrameResized(float newWidth, float newHeight);
		bool		AddItem(void *item);
		bool		AddItem(void *item, long atIndex);
		bool		AddList(BList *newItems);
		bool		AddList(BList *newItems, long atIndex);
		bool		RemoveItem(void * item);
		void		*RemoveItem(long index);

virtual	long		SetTarget(BHandler *target);
virtual long		SetTarget(BLooper *target, bool preferred);
virtual	void		SetSelectionMessage(BMessage *message);
virtual	void		SetInvocationMessage(BMessage *message);

		BHandler	*Target(BLooper **looper = NULL) const;
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
		bool		IsItemSelected(long index) const;
		long		CurrentSelection() const;

virtual void		Invoke(long index);

		void		SortItems(int (*cmp)(const void *, const void *));
	
virtual	void		AttachedToWindow();
virtual void		SetFontName(const char *name);
virtual void		SetSymbolSet(const char *name);
virtual void		SetFontSize(float pointSize);
virtual void		SetFontShear(float degrees);
virtual void		SetFontRotation(float degrees);

// ------------------------------------------------------------------

protected:

virtual	void		DrawItem(BRect updateRect, long index);
virtual	void		HighlightItem(bool on, long index);
virtual float		ItemHeight();
		BRect		ItemFrame(long index);
		float		BaselineOffset();


// ------------------------------------------------------------------

private:
		void		FixupScrollBar();
		void		InvalidateFrom(long y);
		BScrollBar	*ScrollBar();
		void		Invoke(BMessage *msg, long index);
		void		FontChanged();
		void		DrawFocusIndicator(bool smart);

		BList		fList;
		long		fSelected;
		BScrollBar	*fScroll;
		float		fItemHeight;
		float		fBaselineOffset;
		BMessage	*fSelectMessage;
		BMessage	*fInvokeMessage;
		BHandler	*fTarget;
		BLooper		*fLooper;
};

inline void *BListView::Items() const
	{ return fList.Items(); }

inline bool BListView::IsItemSelected(long index) const
	{ return(fSelected == index); }

inline long BListView::CurrentSelection() const
	{ return(fSelected); }

#endif
