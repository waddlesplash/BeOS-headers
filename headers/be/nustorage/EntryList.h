/* ++++++++++
	FILE:	EntryList.h
	Pure virtual directory scanning functions

	Copyright (c) 1997 by Be Incorporated.  All Rights Reserved.
+++++ */

#pragma once
#ifndef _ENTRY_LIST_H
#define _ENTRY_LIST_H

#include <dirent.h>
#include <limits.h>

#include <SupportDefs.h>

class BEntry;
struct entry_ref;

class BEntryList
{
public:

virtual status_t		GetNextEntry(BEntry *entry, 
									 bool traverse=false) = 0;
virtual status_t		GetNextRef(entry_ref *ref) = 0;
virtual int32			GetNextDirents(struct dirent *buf, 
						   		size_t length, int32 count = INT_MAX) = 0;

virtual status_t		Rewind() = 0;
virtual int32			CountEntries() = 0;
};

#endif
