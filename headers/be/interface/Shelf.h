//******************************************************************************
//
//	File:		Shelf.h
//
//	Copyright 1996-97, Be Incorporated
//
//******************************************************************************

#pragma once

#ifndef _SHELF_H
#define _SHELF_H

#include <View.h>
#include <List.h>
#include <DataIO.h>
#include <MessageFilter.h>

class _TShelfFilter_;
class BEntry;

class BShelf : public BHandler {
public:
					BShelf(BView *view,
							bool allow_drags = true,
							const char *shelf_type = NULL);
					BShelf(const entry_ref *ref,
							BView *view,
							bool allow_drags = true,
							const char *shelf_type = NULL);
					BShelf(BDataIO *stream,
							BView *view,
							bool allow_drags = true,
							const char *shelf_type = NULL);
					BShelf(BMessage *data);
virtual				~BShelf();

virtual	status_t	Archive(BMessage *data, bool deep = true) const;
static	BShelf		*Instantiate(BMessage *data);

virtual	void		MessageReceived(BMessage *msg);
		status_t	Save();
virtual	void		SetDirty(bool state);
		bool		IsDirty() const;

virtual BHandler	*ResolveSpecifier(BMessage *msg,
									int32 index,
									BMessage *specifier,
									int32 form,
									const char *property);
virtual status_t	GetSupportedSuites(BMessage *data);

virtual status_t	Perform(uint32 d, void *arg);
		filter_result	AddReplicant(BMessage *data, BPoint pt);
		bool		AllowsDragging() const;

protected:
virtual bool 		CanAcceptReplicantMessage(BMessage *) const;
virtual bool 		CanAcceptReplicantView(BRect, BView *, BMessage *) const;
virtual BPoint 		AdjustReplicantBy(BRect, BMessage *) const;

private:
friend class _TShelfFilter_;

virtual	void		_ReservedShelf1();
virtual	void		_ReservedShelf2();
virtual	void		_ReservedShelf3();
virtual	void		_ReservedShelf4();
virtual	void		_ReservedShelf5();

					BShelf(const BShelf&);
		BShelf		&operator=(const BShelf &);

		status_t	_Archive(BMessage *data) const;
		void		InitData(BEntry *entry,
							BDataIO *stream,
							BView *view,
							bool allow_drags);

		BView			*fContainerView;
		BDataIO			*fStream;
		BEntry			*fEntry;
		BList			fViews;
		_TShelfFilter_	*fFilter;
		bool			fAllowDragging;
		bool			fDirty;

		uint32			_reserved[5];
};

#endif
