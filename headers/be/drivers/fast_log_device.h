/* 
	Copyright (c) 2002-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	Device interface of fast logging facilities.
	
	
	Internal interface. For full description see fast_log.h
*/

#ifndef FAST_LOG_DEVICE_H
#define FAST_LOG_DEVICE_H

#include <drivers/fast_log.h>
#include <Drivers.h>


// one entry in logging buffer
typedef struct fast_log_entry {
	// client handle.
	// this must be first as it is checked against NULL
	// by reader to detect overflown entries; moving it
	// to a later offset would make reading of it dangerous
	// as it could be located byond end of buffer 
	// (perhaps this could be handled as well, but it
	//  would make things more complicated)
	struct fast_log_connection *handle;
	// event type
	int16 event;
	// number of entries in "params"
	int16 num_params;
	// timestamp
	bigtime_t time;
	// parameters
	uint32 params[1];
} fast_log_entry;


#define FASTLOG_ENTRY_SIZE( num_params ) \
	(sizeof( fast_log_entry ) + sizeof( uint32 ) * ((num_params)-1))

// data concurrently accessed by clients
typedef struct fast_log_shared_info {
	// offset in logging buffer for next write.
	// bit 31 is set for upper buffer half and is rest for lower buffer half
	vuint32 offset_alloc;
	// offset of end of last write
	vuint32 offset_filled;
	// size of one half of log buffer
	uint32	buffer_size;
} fast_log_shared_info;

// connection info filled out during FASTLOG_INIT_CONNECTION.
// "prefix" and "types" must be filled out by caller, everything else is 
// filled out by driver; the driver has its own copy, so you can
// safely discard it and its elements if not used anymore with one exception:
// the areas must be deleted manually after uninit because of safety
// important: there is only one connection allowed per file handle
typedef struct fast_log_conn_info {
	const char 				*prefix;			// in: message prefix
	const fast_log_event_type *types;			// in: list of event types
	char 					*buffer;			// log buffer
	area_id 				buffer_area;		// its area
	fast_log_shared_info	*shared_info;		// shared info
	area_id					shared_info_area;	// its area
	fast_log_handle			handle;				// client handle
	int						file_handle;		// reserved for user
} fast_log_conn_info;

// ioctl commands
enum {
	// init connection
	FASTLOG_INIT_CONNECTION = B_DEVICE_OP_CODES_END + 1,
	FASTLOG_UNINIT_CONNECTION
};

// name of device (under /dev)
#define FAST_LOG_DEVFS_NAME "fast_log"

#endif
