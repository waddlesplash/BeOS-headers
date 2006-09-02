/* 
	Copyright (c) 2002-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	Fast logging facilities.
	
	This logging is much faster then dprintf and is saver
	against buffer overflow conditions.
	
	Clients have to define events by creating an array of 
	fast_log_type entries, each consisting of a code and the
	associated human-readable description. During logging, 
	only the code is stored to save space and time. Also, 
	all arguments are stored binary (currently, they must 
	be of type uint32). Conversion to human-readable text is
	post-poned until the logging data is read or a client
	connection is closed (as this invalidates the event-
	description binding). To remove all logging-related code,
	you can use FAST_LOGxxx macros. Define USE_FAST_LOG 
	before including this header to map them to function calls,
	undefine it (e.g. in release version) to disable calls.
	
	The reader interface is /dev/FAST_LOG_DEVFS_NAME. This
	device can only be read from (no seeking or further
	functionality) and does not block if there is no data.
	This is because if you want to store the log into a
	file, the file access may lead to further logging data,
	so doing a sleep between reads saves logging entries.
*/

#ifndef FAST_LOG_H
#define FAST_LOG_H

#include <pnp/pnp_module.h>

// one event type as defined by client
typedef struct fast_log_event_type {
	// code of event (zero means end-of-list)
	int16 event;
	// human-readable description
	const char *description;
} fast_log_event_type;


// handle of client connection
typedef struct fast_log_connection *fast_log_handle;


// interface for clients
typedef struct fast_log_interface {
	// open client connection
	// prefix - prefix to print in log before each event
	// types  - array of event types; last entry must have event=0
	// note: neither prefix nor types are copied, so they must stay valid
	// until stop_log()!
	fast_log_handle (*start_log)( const char *prefix, const fast_log_event_type *types );
	// close client connection
	void (*stop_log)( fast_log_handle handle );
	
	// log an entry without arguments
	void (*log_0)( fast_log_handle handle, int event );
	// log an entry with one argument
	void (*log_1)( fast_log_handle handle, int event, uint32 param1 );
	// log an entry with two arguments
	void (*log_2)( fast_log_handle handle, int event, uint32 param1, uint32 param2 );
	// log an entry with three arguments
	void (*log_3)( fast_log_handle handle, int event, uint32 param1, uint32 param2, uint32 param3 );
	// log an entry with four arguments
	void (*log_4)( fast_log_handle handle, int event, uint32 param1, uint32 param2, uint32 param3, uint32 param4 );
	
	// log an entry with n arguments
	// don't cheat on num_params!
	void (*log_n)( fast_log_handle handle, int event, int num_params, ... );
} fast_log_interface;

#define FAST_LOG_INTERFACE "fast_log/v1"

#define FAST_LOG_MODULE_NAME "generic/fast_log"


// define USE_FAST_LOG to enable, undefine to disable logging
#ifdef USE_FAST_LOG
#define FAST_LOG0( handle, event ) fast_log->log_0( handle, event )
#define FAST_LOG1( handle, event, param ) fast_log->log_1( handle, event, param )
#define FAST_LOG2( handle, event, param1, param2 ) fast_log->log_2( handle, event, param1, param2 )
#define FAST_LOG3( handle, event, param1, param2, param3 ) fast_log->log_3( handle, event, param1, param2, param3 )
#define FAST_LOGN( handle, event, num_params... ) fast_log->log_n( handle, event, num_params )
#else
#define FAST_LOG0( handle, event )
#define FAST_LOG1( handle, event, param )
#define FAST_LOG2( handle, event, param1, param2 )
#define FAST_LOG3( handle, event, param1, param2, param3 )
#define FAST_LOGN( handle, event, num_params... )
#endif


#endif
