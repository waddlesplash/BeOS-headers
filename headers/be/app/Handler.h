//******************************************************************************
//
//	File:			Handler.h
//
//	Description:	Client handler class.
//
//	Copyright 1995-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************


#ifndef _HANDLER_H
#define _HANDLER_H

#include <Archivable.h>
#include <Message.h>

class BLooper;
class BMessageFilter;
class BMessage;
class BList;

class BHandler : public BArchivable {

public:
					BHandler(const char *name = NULL);
virtual				~BHandler();

					BHandler(BMessage *data);
static	BHandler	*Instantiate(BMessage *data);
virtual	status_t	Archive(BMessage *data, bool deep = true) const;

virtual	void		MessageReceived(BMessage *message);
		BLooper		*Looper() const;

		const char	*Name() const;
		void		SetName(const char *name);

virtual	void		SetNextHandler(BHandler *handler);
		BHandler	*NextHandler() const;

virtual	void		AddFilter(BMessageFilter *filter);
virtual	bool		RemoveFilter(BMessageFilter *filter);
virtual	void		SetFilterList(BList *filters);
		BList		*FilterList();

// functions related to the scripting architecture.
virtual BHandler	*ResolveSpecifier(BMessage *msg,
									int32 index,
									BMessage *specifier,
									int32 form,
									const char *property);
virtual status_t	GetSupportedSuites(BMessage *data);

virtual status_t	Perform(uint32 d, void *arg);

private:
friend inline int32 _get_object_token_(const BHandler *);
friend class BLooper;
friend class BMessageFilter;

virtual	void		_ReservedHandler1();
virtual	void		_ReservedHandler2();
virtual	void		_ReservedHandler3();
virtual	void		_ReservedHandler4();

		void		InitData(const char *name);

					BHandler(const BHandler &);
		BHandler	&operator=(const BHandler &);

		int32		fToken;
		char		*fName;
		BLooper		*fLooper;
		BHandler	*fNextHandler;
		BList		*fFilters;
		uint32		_reserved[4];
};

#endif
