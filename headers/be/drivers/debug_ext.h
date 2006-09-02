/* 
	Copyright (c) 2002-03, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	Advanced interface for dprintf message calls.


	There are three kinds of messages:
		flow: used to trace execution
		info: tells things that are important but not an error
		error: used if something has gone wrong
	
	Common usage is 
		SHOW_{FLOW,INFO,ERROR}( seriousness, format string, parameters... );
	 	SHOW_{FLOW,INFO,ERROR}0( seriousness, string );
	
	with
		seriousness: the smaller the more serious (0..3)
		format string, parameters: normal printf stuff
	
	To specify the module that created the message you have
	to define a string called
		DEBUG_MSG_PREFIX
	
	You specify the maximum seriousness level dynamically by defining 
	the following variables/macros
		debug_level_flow
		debug_level_info
		debug_level_error
	
	You _can_ specify the maximum seriousness level statically by defining
		DEBUG_MAX_LEVEL_FLOW
		DEBUG_MAX_LEVEL_INFO
		DEBUG_MAX_LEVEL_ERRROR
	
	You _can_ ask to delay execution after each printed message 
	by defining the duration (in ms) via
		DEBUG_WAIT_ON_MSG (for flow and info)
		DEBUG_WAIT_ON_ERROR (for error)
*/


#ifndef __DEBUG_EXT_H__
#define __DEBUG_EXT_H__

#ifdef DEBUG_WAIT_ON_MSG
#define DEBUG_WAIT snooze( DEBUG_WAIT_ON_MSG );
#else
#define DEBUG_WAIT 
#endif

#ifdef DEBUG_WAIT_ON_ERROR
#define DEBUG_WAIT_ERROR snooze( DEBUG_WAIT_ON_ERROR );
#else
#define DEBUG_WAIT_ERROR
#endif

#ifndef DEBUG_MAX_LEVEL_FLOW
#define DEBUG_MAX_LEVEL_FLOW 4
#endif

#ifndef DEBUG_MAX_LEVEL_INFO
#define DEBUG_MAX_LEVEL_INFO 4
#endif

#ifndef DEBUG_MAX_LEVEL_ERROR
#define DEBUG_MAX_LEVEL_ERROR 4
#endif


#ifndef DEBUG_MSG_PREFIX
#error you need to define DEBUG_MSG_PREFIX with the module name
#endif

#define FUNC_NAME DEBUG_MSG_PREFIX __FUNCTION__ ": "

#ifdef ASSERT
#undef ASSERT
#endif

#ifdef DEBUG

// Only clog the syslog with this stuff when debugging.	
	#define SHOW_FLOW(seriousness, format, param...) \
		do { if( seriousness <= debug_level_flow && seriousness <= DEBUG_MAX_LEVEL_FLOW ) { \
			dprintf( "%s"##format"\n", FUNC_NAME, param ); DEBUG_WAIT \
		}} while( 0 )
	
	#define SHOW_FLOW0(seriousness, format) \
		do { if( seriousness <= debug_level_flow && seriousness <= DEBUG_MAX_LEVEL_FLOW ) { \
			dprintf( "%s"##format"\n", FUNC_NAME); DEBUG_WAIT \
		}} while( 0 )
	
	#define SHOW_INFO(seriousness, format, param...) \
		do { if( seriousness <= debug_level_info && seriousness <= DEBUG_MAX_LEVEL_INFO ) { \
			dprintf( "%s"##format"\n", FUNC_NAME, param ); DEBUG_WAIT \
		}} while( 0 )
	
	#define SHOW_INFO0(seriousness, format) \
		do { if( seriousness <= debug_level_info && seriousness <= DEBUG_MAX_LEVEL_INFO ) { \
			dprintf( "%s"##format"\n", FUNC_NAME); DEBUG_WAIT \
		}} while( 0 )
	
	#define ASSERT(cond) \
		do { if (!(cond)) { \
			panic( "%s: assertion failed: %s", FUNC_NAME, #cond); \
		}} while( 0 )
	
	#define ASSERTF(cond, fmt, param...) \
		do { if (!(cond)) { \
			panic( "%s: assertion failed: %s\n"##fmt, FUNC_NAME, #cond, param ); \
		}} while( 0 )
	
#else


	#define SHOW_FLOW(seriousness, format, param...)	do { } while(0)
	#define SHOW_FLOW0(seriousness, format) 			do { } while(0)
	#define SHOW_INFO(seriousness, format, param...)	do { } while(0)
	#define SHOW_INFO0(seriousness, format)				do { } while(0)
	#define ASSERT(cond)					do { } while(0)
	#define ASSERTF(cond...)					do { } while(0)

#endif	// DEBUG


// Showing errors is more critical.
#define SHOW_ERROR(seriousness, format, param...) \
	do { if( seriousness <= debug_level_error && seriousness <= DEBUG_MAX_LEVEL_ERROR ) { \
		dprintf( "%s"##format"\n", FUNC_NAME, param ); DEBUG_WAIT_ERROR \
	}} while( 0 )

#define SHOW_ERROR0(seriousness, format) \
	do { if( seriousness <= debug_level_error && seriousness <= DEBUG_MAX_LEVEL_ERROR ) { \
		dprintf( "%s"##format"\n", FUNC_NAME); DEBUG_WAIT_ERROR \
	}} while( 0 )

#endif	// header
