/* 
	Copyright (c) 2004, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	User space version of fast logging facilities.
	
	For precise info, see <drivers/fast_log.h>.
	
	This logging interacts _directly_ with kernel logging,
	so if the application crashes during logging, the kernel
	can lock up. On the positive side, logging generated
	via this library is smoothly integrated into kernel 
	fast logging.
*/

#ifndef FAST_LOG_USER_H
#define FAST_LOG_USER_H

#define PURE_MALLOC

#include <drivers/fast_log_device.h>

// open client connection
// prefix - prefix to print in log before each event
// types  - array of event types; last entry must have event=0
// note: neither prefix nor types are copied, so they must stay valid
// until stop_log()!
fast_log_conn_info *fast_log_start_log( const char *prefix, const fast_log_event_type *types );
// close client connection
void fast_log_stop_log( fast_log_conn_info *info );

// log an entry without arguments
void fast_log_log_0( fast_log_conn_info *info, int event );
// log an entry with one argument
void fast_log_log_1( fast_log_conn_info *info, int event, uint32 param1 );
// log an entry with two arguments
void fast_log_log_2( fast_log_conn_info *info, int event, uint32 param1, uint32 param2 );
// log an entry with three arguments
void fast_log_log_3( fast_log_conn_info *info, int event, uint32 param1, uint32 param2, uint32 param3 );
// log an entry with four arguments
void fast_log_log_4( fast_log_conn_info *info, int event, uint32 param1, uint32 param2, uint32 param3, uint32 param4 );

// log an entry with n arguments
// don't cheat on num_params!
void fast_log_log_n( fast_log_conn_info *info, int event, int num_params, ... );


#endif
