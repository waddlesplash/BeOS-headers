/*******************************************************************************
**
**	File:		OutlineListView.h
**
**	Description:	Hierarchical list view with collapsible items
**
**	Copyright 1997, Be Incorporated
**
*******************************************************************************/

#pragma once

#ifndef _OUTLINE_LIST_VIEW_H
#define _OUTLINE_LIST_VIEW_H

#include <ListView.h>
#include <ListItem.h>


class BOutlineListView : public BListView {
public:
					BOutlineListView(BRect frame, const char * name,
						list_view_type type = B_SINGLE_SELECTION_LIST,
						uint32 resizeMask = B_FOLLOW_LEFT | B_FOLLOW_TOP,
						uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS 
							| B_NAVIGABLE);
					BOutlineListView(BMessage *data);
virtual 			~BOutlineListView();

static	BListView	*Instantiate(BMessage *data);
virtual	status_t	Archive(BMessage *data, bool deep = true) const;

virtual	void 		MouseDown(BPoint where);
virtual	void 		KeyDown(const char *bytes, int32 numBytes);
virtual	void		FrameMoved(BPoint new_position);
virtual	void		FrameResized(float new_width, float new_height);
virtual	void 		MouseUp(BPoint where);
	
virtual bool 		AddUnder(BListItem *item, BListItem *underItem);
						// adds <item> as a first subitem in the 
						// <underItem> hierarchy

					// Indices in AddItem and RemoveItem refer to the full
					// outline list including items that are collapsed and 
					// not visible
virtual bool 		AddItem(BListItem *item);
virtual bool		AddItem(BListItem *item, int32 fullListIndex);
virtual bool		AddList(BList *newItems);
virtual bool		AddList(BList *newItems, int32 fullListIndex);

virtual bool		RemoveItem(BListItem *item);
virtual BListItem	*RemoveItem(int32 fullListIndex);
virtual bool		RemoveItems(int32 fullListIndex, int32 count);


					// The following calls operate on the full outline list, 
					// including items that are collapsed and not visible in the
					// list
		BListItem	*FullListItemAt(int32 fullListIndex) const;
		int32		FullListIndexOf(BPoint point) const;
		int32		FullListIndexOf(BListItem *item) const;
		BListItem	*FullListFirstItem() const;
		BListItem	*FullListLastItem() const;
		bool		FullListHasItem(BListItem *item) const;
		int32		FullListCountItems() const;
		int32		FullListCurrentSelection(int32 index = 0) const;
virtual	void		MakeEmpty();
		bool		FullListIsEmpty() const;
		void		FullListDoForEach(bool (*func)(BListItem *));
		void		FullListDoForEach(bool (*func)(BListItem *, void *), void *);

		BListItem*	Superitem(const BListItem *item);

		void 		Expand(BListItem *item);
		void 		Collapse(BListItem *item);
		
		bool		IsExpanded(int32 fullListIndex);

virtual BHandler	*ResolveSpecifier(BMessage *msg,
										int32 index,
										BMessage *specifier,
										int32 form,
										const char *property);
virtual status_t	GetSupportedSuites(BMessage *data);
virtual status_t	Perform(uint32 d, void *arg);
	
private:
virtual	void		_ReservedOutlineListView1();
virtual	void		_ReservedOutlineListView2();
virtual	void		_ReservedOutlineListView3();
virtual	void		_ReservedOutlineListView4();

		int32		FullListIndex(int32 index) const;
		int32		ListViewIndex(int32 index) const;

virtual	void 		ExpandOrCollapse(BListItem *underItem, bool expand);
						// this call does the real work for Expand and 
						// collapse

					// Draw routines
virtual BRect		LatchRect(BRect itemRect, int32 level) const;
virtual void		DrawLatch(BRect itemRect, int32 level, bool collapsed, 
						bool highlighted, bool misTracked);
						// draw the latch in it's different tracking
						// end collapse modes; may override to draw different
						// latches
virtual	void		DrawItem(BListItem *item, BRect cellRect, bool complete = false);

					// Mouse tracking
static	void 		TrackInLatchItem(void *);
static	void 		TrackOutLatchItem(void *);

		BList		fullList;
		uint32		_reserved[2];
};

#endif
