/* This is a -*- C++ -*- header file */
/*
 * net_settings.h
 * Copyright (c) 1995-1997 Be, Inc.	All Rights Reserved 
 *
 */
#pragma once
#ifndef _NET_SETTINGS_H
#define _NET_SETTINGS_H
#include <SupportDefs.h>

#if __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * Private types 
 */
typedef struct _ns_entry {
	const char *key;
	const char *value;
} _ns_entry_t;

typedef struct _ns_section {
	const char *heading;
	unsigned nentries;
	_ns_entry_t *entries;
} _ns_section_t;


/*
 * Public type, but the data members are private
 */
typedef struct _net_settings {
	int _dirty;
	unsigned _nsections;
	_ns_section_t *_sections;
	char _fname[64];
} net_settings;

/*
 * For finding and setting network preferences
 */
char *find_net_setting(net_settings *ncw, 
					   const char *heading, const char *name, char *value,
					   unsigned nbytes);
status_t set_net_setting(net_settings *ncw, 
						 const char *heading, const char *name, 
						 const char *value);

#if __cplusplus
}
#endif /* __cplusplus */

#endif /* _NET_SETTINGS_H */
