/*
	
	StopWatch.h
	
	Copyright 1994-96 Be, Inc. All Rights Reserved.
	
*/

#ifndef _STOP_WATCH_H
#define _STOP_WATCH_H

#ifndef _OBJECT_H
#include <Object.h>
#endif

class BStopWatch : public BObject {
public:
		BStopWatch(const char *name);
virtual		~BStopWatch();

private:
	double	fStart;
	const char	*fName;
};

#endif
