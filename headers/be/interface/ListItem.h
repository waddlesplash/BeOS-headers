/*******************************************************************************
/
/	File:			ListItem.h
/
/   Description:    BListView represents a one-dimensional list view. 
/
/	Copyright 1996-98, Be Incorporated, All Rights Reserved
/
*******************************************************************************/

#ifndef _LIST_ITEM_H
#define _LIST_ITEM_H

#include <BeBuild.h>
#include <Archivable.h>
#include <Rect.h>
#include <interface/Bitmap.h>
#include <support/String.h>

class BFont;
class BMessage;
class BOutlineListView;
class BView;
class BString;
namespace Z {
	namespace Locale {
		class AutoLocale;
	}
}

/*----------------------------------------------------------------*/
/*----- BListItem class ------------------------------------------*/

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

virtual status_t	Perform(perform_code d, void *arg);

		bool 		IsExpanded() const;
		void 		SetExpanded(bool expanded);
		uint32 		OutlineLevel() const;

/*----- Private or reserved -----------------------------------------*/
private:
friend class BOutlineListView;

		bool 		HasSubitems() const;

virtual	void		_ReservedListItem1();
virtual	void		_ReservedListItem2();

					BListItem(const BListItem &);
		BListItem	&operator=(const BListItem &);

		/* calls used by BOutlineListView*/
		bool 		IsItemVisible() const;
		void 		SetItemVisible(bool);

		float		fWidth;
		float		fHeight;
		uint32 		fLevel;
		uint32		_reserved[2];
		bool		fSelected;
		bool		fEnabled;
		bool 		fExpanded;
		bool 		fHasSubitems : 1;
		bool 		fVisible : 1;
};


/*----------------------------------------------------------------*/
/*----- BStringItem class ----------------------------------------*/

class BStringItem : public BListItem {
public:
					BStringItem(const char *text, 
						uint32 outlineLevel = 0, bool expanded = true);
virtual				~BStringItem();
					BStringItem(BMessage *data);
static	BArchivable	*Instantiate(BMessage *data);
virtual	status_t	Archive(BMessage *data, bool deep = true) const;

virtual	void		DrawItem(BView *owner, BRect frame, bool complete = false);
virtual	void		SetText(const char *text);
		const char	*Text() const;
		void		SetBaselineOffset(float off);
		float		BaselineOffset() const;
virtual	void		Update(BView *owner, const BFont *font);

virtual status_t	Perform(perform_code d, void *arg);

private:
friend class Z::Locale::AutoLocale;

virtual	void		_ReservedStringItem1();
virtual	void		_ReservedStringItem2();

					BStringItem(const BStringItem &);
		BStringItem	&operator=(const BStringItem &);

		char		*fText;
		float		fBaselineOffset;
		uint32		_reserved[2];
};


/*----------------------------------------------------------------*/
/*----- libzeta BitmapItem class ---------------------------------*/

namespace Z {
	namespace Interface {
		
class BitmapItem : public BStringItem
{
	public:
						BitmapItem(const BString _label, const BBitmap& _icon);
		virtual			~BitmapItem();
						
		virtual	void		DrawItem(BView* _owner, BRect _bounds, bool _complete);
		virtual	void		Update(BView* _owner, const BFont* _font);
		virtual	void		SetBitmap(const BBitmap& _bitmap);
		
		const BBitmap&		GetBitmap() const;
		
	private:
				void		AdjustHeight();
				void		UpdateMultiline(const BFont& _font);
					
	private:
		BBitmap		fIcon;
		float		fLineHeight;
};

	}	// NS Interface
}	// ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Interface::BitmapItem;
#endif

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/

#endif /* _LIST_ITEM_H */
