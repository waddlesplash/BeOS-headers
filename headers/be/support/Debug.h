/*
	
	Debug.h
	
	Copyright 1994-96 Be, Inc. All Rights Reserved.
	
*/

#ifndef _DEBUG_H
#define _DEBUG_H

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifndef _STDARG_H
#include <stdarg.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _MALLOC_H
#include <malloc.h>
#endif

#ifndef _OS_H
#include <OS.h>
#endif

/* runtime switch for enabling the debug code */
#ifdef __cplusplus
extern "C" {
#endif
	extern bool _rtDebugFlag;
	bool _debugFlag();
	bool _setDebugFlag(bool);
	void _setHeapCheck(bool);
	void _heapCheckFlag(bool);
	
	int _debugPrintf(const char *, ...);
	int _sPrintf(const char *, ...);
	int _xdebugPrintf(const char *, ...);
	int _debuggerAssert(const char *, int, char *);
#ifdef __cplusplus
	}
#endif

#if DEBUG
	#define SET_DEBUG_ENABLED(FLAG)	_setDebugFlag(FLAG)
	#define	IS_DEBUG_ENABLED()		_debugFlag()
	
	#define SET_HEAP_CHECK(FLAG)	_setHeapCheck(FLAG)
	#define	IS_HEAP_CHECK_ENABLED()	_heapCheckFlag()

	#define HEAP_STATS()			_debugPrintf("\nHeap Size: %d bytes\n\
Used blocks: %d (%d bytes)\nFree blocks: %d (%d bytes)\n",\
mstats().bytes_total, mstats().chunks_used, mstats().bytes_used, mstats().chunks_free, mstats().bytes_free);


	#define SERIAL_PRINT(ARGS)		_sPrintf ARGS
	#define PRINT(ARGS) 			_debugPrintf ARGS
	#define PRINT_OBJECT(OBJ)		if (_rtDebugFlag) {		\
										PRINT(("%s\t", #OBJ));	\
										OBJ.PrintToStream(); 	\
										} ((void) 0)
	#define TRACE()				_debugPrintf("File: %s, Line: %d, Thread: %d\n", \
									__FILE__, __LINE__, find_thread(NULL))
	
	#define SERIAL_TRACE()		_sPrintf("File: %s, Line: %d, Thread: %d\n", \
									__FILE__, __LINE__, find_thread(NULL))
	
	#define DEBUGGER(MSG)		if (_rtDebugFlag) debugger(MSG)
	#define ASSERT(E)			(!(E) ? _debuggerAssert(__FILE__,__LINE__, #E) \
										: (int)0)

#else
	#define SET_DEBUG_ENABLED(FLAG)	(void)0
	#define	IS_DEBUG_ENABLED()		(void)0
	
	#define SET_HEAP_CHECK(FLAG) 	(void)0
	#define HEAP_STATS()			(void)0

	#define SERIAL_PRINT(ARGS)		(void)0
	#define PRINT(ARGS)				(void)0
	#define PRINT_OBJECT(OBJ)		(void)0
	#define TRACE()					(void)0
	#define SERIAL_TRACE()			(void)0
	
	#define DEBUGGER(MSG)			(void)0
	#define ASSERT(E)				(void)0
#endif

#endif

