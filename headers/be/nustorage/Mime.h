/*****************************************************************************
//
//	File:			Mime.h
//
//	Description:	MIME string functions
//
//	Copyright 1997, Be Incorporated, All Rights Reserved.
//
//****************************************************************************/
#pragma once

#ifndef _MIME_H
#define _MIME_H

#include <sys/types.h>
#include <SupportDefs.h>
#include <StorageDefs.h>

#ifdef __cplusplus
extern "C" {
#endif

	int	update_mime_info(const char *path,
						int recursive,
						int synchronous,
						int force);
	status_t create_app_meta_mime(const char *path,
									int recursive,
									int synchronous,
									int force);
	status_t get_device_icon(const char *dev, void *icon, int32 size);

	const uint32 B_MIME_STRING_TYPE	= 'MIMS';

#ifdef __cplusplus
}
#endif

enum icon_size {
	B_LARGE_ICON = 32,
	B_MINI_ICON = 16
};

#ifdef __cplusplus

#include <Message.h>
#include <File.h>
#include <Entry.h>

class BBitmap;
class BResources;

enum app_verb {
	B_OPEN
};

extern const char *B_APP_MIME_TYPE;			// "application/x-be-executable"

/* ------------------------------------------------------------- */

class BMimeType	{

public:
					BMimeType();
					BMimeType(const char *MIME_type);
virtual				~BMimeType();

		status_t	SetTo(const char *MIME_type);
		void		Unset();
		status_t 	InitCheck() const;

		// these functions simply perform string manipulations
		const char	*Type() const;
		bool		IsValid() const;
		bool		IsSupertypeOnly() const;
		bool		IsInstalled() const;
		status_t	GetSupertype(BMimeType *super_type) const;

		// These functions are for managing data in the meta mime file
		status_t	Install();
		status_t	Delete();
		status_t	GetIcon(BBitmap *icon, icon_size) const;
		status_t	GetPreferredApp(char *signature,
									app_verb verb = B_OPEN) const;
		status_t	GetAttrInfo(BMessage *info) const;
		status_t	GetFileExtensions(BMessage *extensions) const;
		status_t	GetShortDescription(char *description) const;
		status_t	GetLongDescription(char *description) const;
		status_t	GetSupportingApps(BMessage *signatures) const;

		status_t	SetIcon(const BBitmap *icon, icon_size);
		status_t	SetPreferredApp(const char *signature,
									app_verb verb = B_OPEN);
		status_t	SetAttrInfo(const BMessage *info);
		status_t	SetFileExtensions(const BMessage *extensions);
		status_t	SetShortDescription(const char *description);
		status_t	SetLongDescription(const char *description);

static	status_t	GetInstalledSupertypes(BMessage *super_types);
static	status_t	GetInstalledTypes(BMessage *types);
static	status_t	GetInstalledTypes(const char *super_type,
									BMessage *subtypes);
static	bool		IsValid(const char *string);

		// for application signatures only.
		status_t	GetIconForType(const char *type,
								BBitmap *icon,
								icon_size which) const;
		status_t	SetIconForType(const char *type,
								const BBitmap *icon,
								icon_size which);
		status_t	GetAppHint(entry_ref *ref) const;
		status_t	SetAppHint(const entry_ref *ref);


		/* Misnomer.  Use SetTo instead. */
		status_t	SetType(const char *MIME_type);

private:
friend	class BAppFileInfo;
friend	class BRoster;
friend	status_t	_update_mime_info_(const char *, bool);

virtual	void		_ReservedMimeType1();
virtual	void		_ReservedMimeType2();
virtual	void		_ReservedMimeType3();

		BMimeType	&operator=(const BMimeType &);
					BMimeType(const BMimeType &);

		void		InitData(const char *type);
		status_t	OpenFile(bool create_file = FALSE,
							dev_t dev = -1) const;
		status_t	CloseFile() const;
		status_t	SetSupportedTypes(const BMessage *types);

		char		*fType;
		BFile		*fMeta;
		BResources	*fResources;
		entry_ref	fRef;
		int			fWhere;
		status_t	fCStatus;
		uint32		_reserved[3];
};

#endif
#endif
