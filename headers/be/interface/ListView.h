/*******************************************************************************
**
**	File:		ListView.h
**
**	Description:	client list view class.
**
**	Written by:	Greg White
**
**	Copyright 1992-93, Be Incorporated
**
*******************************************************************************/
#ifndef _LIST_VIEW_H
#define _LIST_VIEW_H

class BList;

class BListView : public BView
{

public:
			BListView(const BRect *frame, char *name,
				  long resizeMask, long flags);
			BListView();
virtual			~BListView();
virtual	void		AttachedToWindow();
virtual	char		*ClassName();
virtual	void		Draw(BRect *updateRect);
virtual	void		MouseDown(BPoint where);
virtual	void		KeyDown(ulong aKey);
	bool		AddItem(void *);
	bool		AddItem(void *, long atIndex);
	bool		RemoveItem(void *);
	void		*RemoveItem(long index);
	void		*RemoveLastItem();
	void		*GetItem(long);
	long		GetIndex(void *);
	void		*FirstItem();
	void		*LastItem();
	bool		HasItem(void *);
	long		CountItems();
	void		MakeEmpty();
	bool		IsEmpty();
	void		DoForEach(void (*func)(void *));
	void		DoForEach(void (*func)(void *, void *), void *);
virtual	void		DrawItem(BRect *updateRect, void *item);
virtual long		ItemHeight();
	bool		IsSelected(void *item) { return(selected == item); };
	void		GetItemFrame(void *item, BRect *bounds);
	void		GetItemFrame(long index, BRect *bounds);
	void		InvalidateItem(void *item);
	void		InvalidateItem(long index);
	bool		Select(void *item);
	bool		Select(long index);
virtual	void		ItemSelected(void *item);
virtual void		ItemOpened(void *item);
	void		*Selected() { return(selected); };
	bool		AddItems(void **items, long count);

private:
	void		FixupScrollBar();
	void		InvalidateFrom(long y);
	BScrollBar	*ScrollBar();
	BList		*list;
	void		*selected;
	ulong		clickTime;
	BScrollBar	*scroll;
};

#endif
