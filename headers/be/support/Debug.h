/*
	
	Debug.h
	
	Copyright 1994 Be, Inc. All Rights Reserved.
	
*/

#ifndef _DEBUG_H
#define _DEBUG_H

#ifndef _SUPPORT_DEFS_H
#include <support/SupportDefs.h>
#endif

#ifndef _STDARG_H
#include <stdarg.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

/* runtime switch for enabling the debug code */
#ifdef __CPLUSPLUS__
extern "C" {
#endif
	extern bool _rtDebugFlag;
	bool _debugFlag();
	bool _setDebugFlag(bool);
	void _setHeapCheck(bool);
	
	int _debugPrintf(char *, ...);
	int _xdebugPrintf(char *, ...);
	int _debuggerAssert(char *, int, char *);
#ifdef __CPLUSPLUS__
	}
#endif

#if DEBUG
	#define DEBUG_ON()		_setDebugFlag(TRUE)
	#define DEBUG_OFF()		_setDebugFlag(FALSE)
	#define	IS_DEBUG_ON()		_debugFlag()
	
	#define HEAP_CHECK_ON()		_setHeapCheck(TRUE);
	#define HEAP_CHECK_OFF()	_setHeapCheck(FALSE);

	#define PRINT(ARGS) 		_debugPrintf ARGS
	#define PRINT_OBJ(OBJ)		if (_rtDebugFlag) {		\
						PRINT(("%s\t", #OBJ));	\
						OBJ.PrintToStream(); 	\
						} ((void) 0)
	#define TRACE()			_debugPrintf("File: %s, Line: %d, pid: %d\n", \
						__FILE__, __LINE__, getpid())
	
	#define DEBUGGER(MSG)	if (_rtDebugFlag) debugger(MSG)
	#define ASSERT(E)	(!(E) ? _debuggerAssert(__FILE__, __LINE__, #E) : (int)0)
	#define PRINT_ASSERT(E)	(!(E) ? _xdebugPrintf("Assert Failed - File: %s, Line: %d. %s\n", __FILE__, __LINE__, #E) : (int)0)

#else
	#define DEBUG_ON()	 	FALSE
	#define DEBUG_OFF()		FALSE
	#define	IS_DEBUG_ON()		FALSE
	
	#define HEAP_CHECK_ON()	 	void(0)
	#define HEAP_CHECK_OFF()	void(0)

	#define PRINT(ARGS)		(void)0
	#define PRINT_OBJ(OBJ)		(void)0
	#define TRACE()			(void)0
	
	#define DEBUGGER(MSG)		(void)0
	#define ASSERT(E)		(void)0
	#define PRINT_ASSERT(E)		(void)0
#endif


/*
 The following Debug stuff is only available from C++ code.
*/
#ifdef __CPLUSPLUS__

#if DEBUG

	#ifndef _OBJECT_H
	#include <support/Object.h>
	#endif
	
	class BStopWatch : public BObject {
	public:
				BStopWatch(const char *name);
	virtual		~BStopWatch();

	private:
		ulong	fStart;
		const char	*fName;
	};

#else

	#define BStopWatch(name)	(void) 0

#endif

#endif

#endif

