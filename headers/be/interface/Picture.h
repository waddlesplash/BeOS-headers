//******************************************************************************
//
//	File:			Picture.h
//
//	Description:	Client picture class.
//
//	Copyright 1995-97, Be Incorporated. All Rights Reserved
//
//******************************************************************************

#pragma once

#ifndef	_PICTURE_H
#define	_PICTURE_H

#include <InterfaceDefs.h>
#include <Rect.h>
#include <Archivable.h>

//--------------------------------------------------------------------------
class	BView;

class BPicture : public BArchivable {

public:
					BPicture();
					BPicture(const BPicture &original);
					BPicture(const void *data, int32 size);
					BPicture(BMessage *data);
virtual				~BPicture();	
static	BPicture	*Instantiate(BMessage *data);
virtual	status_t	Archive(BMessage *data, bool deep = true) const;

		const void	*Data() const;
		int32		DataSize() const;
		
virtual status_t	Perform(uint32 d, void *arg);

private:
friend class BView;

virtual	void		_ReservedPicture1();
virtual	void		_ReservedPicture2();
virtual	void		_ReservedPicture3();

		BPicture	&operator=(const BPicture &);

		void		InitObject(const void *data, int32 size);
		void		set_fields(int32 token, void *data, int32 size);

		int32		server_token;
		void		*server_data;
		int32		server_data_size;
		uint32		_reserved[3];
};

#endif
