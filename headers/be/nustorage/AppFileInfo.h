/****************************************************************************
//
//	File:			AppFileInfo.h
//
//	Description:	File type information
//
//	Copyright 1997, Be Incorporated, All Rights Reserved.
//
/*****************************************************************************/
#pragma once

#ifndef _APP_FILE_INFO_H
#define _APP_FILE_INFO_H

#include <NodeInfo.h>

class BBitmap;
class BMessage;
class BResources;
class BFile;

/* ------------------------------------------------------------- */

struct	version_info {
	uint32	major;
	uint32	middle;
	uint32	minor;
	uint32	variety;
	uint32	internal;
	char	short_info[64];
	char	long_info[256];
};

enum version_kind {
	B_APP_VERSION_KIND,
	B_SYSTEM_VERSION_KIND
};

/* ------------------------------------------------------------- */

class BAppFileInfo: public BNodeInfo {
public:
  					BAppFileInfo();
					BAppFileInfo(BFile *file);
virtual				~BAppFileInfo();

		status_t	SetTo(BFile *file);
		status_t	InitCheck();

virtual	status_t	GetType(char *type) const;
		status_t	GetSignature(char *sig) const;
		status_t	GetAppFlags(uint32 *flags) const;
		status_t	GetSupportedTypes(BMessage *types) const;
		status_t	GetIcon(BBitmap *icon, icon_size which) const;
		status_t	GetVersionInfo(version_info *vinfo, version_kind k) const;
		status_t	GetIconForType(const char *type,
									BBitmap *icon,
									icon_size which) const;

virtual	status_t	SetType(const char *type);
		status_t	SetSignature(const char *sig);
		status_t	SetAppFlags(uint32 flags);
		status_t	SetSupportedTypes(const BMessage *types);
		status_t	SetIcon(const BBitmap *icon, icon_size which);
		status_t	SetVersionInfo(const version_info *vinfo, version_kind k);
		status_t	SetIconForType(const char *type,
									const BBitmap *icon,
									icon_size which);

private:
friend	status_t	_update_mime_info_(const char *, bool);
friend	status_t	_update_app_(const char *, bool);

virtual	void		_ReservedAppFileInfo1();
virtual	void		_ReservedAppFileInfo2();
virtual	void		_ReservedAppFileInfo3();

		BAppFileInfo	&operator=(const BAppFileInfo &);
						BAppFileInfo(const BAppFileInfo &);

		status_t	_SetSupportedTypes(const BMessage *types);
		status_t	UpdateFromRsrc();
		status_t	RealUpdateRsrcToAttr();
		status_t	UpdateMetaMime(const char *path, bool force) const;
		bool		IsApp();
		status_t	GetMetaMime(BMimeType *meta) const;

		BResources	*fResources;
		int			fWhere;
		uint32		_reserved[2];
};

#endif
