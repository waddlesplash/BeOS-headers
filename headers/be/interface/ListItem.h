/*******************************************************************************
**
**	File:		ListItem.h
**
**	Description:	list item class (for use with the BListView class).
**
**	Copyright 1996-97, Be Incorporated
**
*******************************************************************************/

#pragma once

#ifndef _LIST_ITEM_H
#define _LIST_ITEM_H

#include <Rect.h>
#include <Archivable.h>
#include <View.h>
#include <Message.h>

class BFont;
class BView;
class BOutlineListView;

class BListItem : public BArchivable {
public:
					BListItem(uint32 outlineLevel = 0, bool expanded = true);
					BListItem(BMessage *data);
virtual				~BListItem();
virtual	status_t	Archive(BMessage *data, bool deep = true) const;

		float		Height() const;
		float		Width() const;
		bool		IsSelected() const;
		void		Select();
		void		Deselect();

virtual	void		SetEnabled(bool on);
		bool		IsEnabled() const;

		void		SetHeight(float height);
		void		SetWidth(float width);
virtual	void		DrawItem(BView *owner,
							BRect bounds,
							bool complete = false) = 0;
virtual	void		Update(BView *owner, const BFont *font);

virtual status_t	Perform(uint32 d, void *arg);

		// calls used by BOutlineListView
		bool 		IsExpanded() const;
		void 		SetExpanded(bool expanded);
		uint32 		OutlineLevel() const;
		bool 		HasSubitems() const;

private:
friend class BOutlineListView;

virtual	void		_ReservedListItem1();
virtual	void		_ReservedListItem2();

					BListItem(const BListItem &);
		BListItem	&operator=(const BListItem &);

		float		fWidth;
		float		fHeight;
		uint32 		fLevel;
		uint32		_reserved[2];
		bool		fSelected;
		bool		fEnabled;
		bool 		fExpanded;
		bool 		fHasSubitems;
};


/* ---------------------------------------------------------------- */
/* ---------------------------------------------------------------- */
/* ---------------------------------------------------------------- */

class BStringItem : public BListItem {
public:
					BStringItem(const char *text, 
						uint32 outlineLevel = 0, bool expanded = true);
virtual				~BStringItem();
					BStringItem(BMessage *data);
static	BStringItem	*Instantiate(BMessage *data);
virtual	status_t	Archive(BMessage *data, bool deep = true) const;

virtual	void		DrawItem(BView *owner, BRect frame, bool complete = false);
virtual	void		SetText(const char *text);
		const char	*Text() const;
virtual	void		Update(BView *owner, const BFont *font);

virtual status_t	Perform(uint32 d, void *arg);

private:

virtual	void		_ReservedStringItem1();
virtual	void		_ReservedStringItem2();

					BStringItem(const BStringItem &);
		BStringItem	&operator=(const BStringItem &);

		char		*fText;
		float		fBaselineOffset;
		uint32		_reserved[2];
};

#endif
