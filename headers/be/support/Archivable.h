//******************************************************************************
//
//	File:		Archivable.h
//
//	Description:	Super class to any class thaht wants to be archivable
//
//	Copyright 1997, Be Incorporated
//
//******************************************************************************


#ifndef	_ARCHIVABLE_H
#define	_ARCHIVABLE_H

#include <SupportDefs.h>

//------------------------------------------------------------------------------
class BMessage;

class BArchivable {
public:
					BArchivable();
virtual				~BArchivable();	

					BArchivable(BMessage *from);
virtual	status_t	Archive(BMessage *into, bool deep = true) const;
static	BArchivable	*Instantiate(BMessage *from);

					/*
					 The Perform() function is reserved for use by Be.
					 It is to be used only as directed.
					*/
virtual status_t	Perform(uint32 d, void *arg);

private:

virtual	void		_ReservedArchivable1();
virtual	void		_ReservedArchivable2();
virtual	void		_ReservedArchivable3();

		uint32		_reserved[2];
};

//------------------------------------------------------------------------------

typedef BArchivable *(*instantiation_func) (BMessage *); 

BArchivable			*instantiate_object(BMessage *from);

bool				validate_instantiation(	BMessage *from,
											const char *class_name);
instantiation_func	find_instantiation_func(const char *class_name);
instantiation_func	find_instantiation_func(BMessage *archive_data);

#endif
