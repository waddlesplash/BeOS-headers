/***************************************************************************
//
//	File:			Alias.h
//
//	Description:	path->alias->path functions
//
//	Copyright 1992-97, Be Incorporated, All Rights Reserved.
//
//*************************************************************************/

#ifndef _ALIAS_H
#define _ALIAS_H

#include <SupportDefs.h>

class	BPath;
class	BDataIO;

status_t		resolve_link(const char *path, BPath *result,
					bool block = FALSE);

status_t		write_alias(const char *path, BDataIO *s, size_t *len = NULL);
status_t		write_alias(const char *path, void *buf, size_t *len);

status_t		read_alias(BDataIO *s, BPath *result, size_t *len = NULL,
					bool block = FALSE);
status_t		read_alias(const void *buf, BPath *result, size_t *len,
					bool block = FALSE);

#endif
