/*
	
	StopWatch.h
	
	Copyright 1994-97 Be, Inc. All Rights Reserved.
	
*/

#pragma once

#ifndef _STOP_WATCH_H
#define _STOP_WATCH_H

#include <SupportDefs.h>

class BStopWatch {
public:
					BStopWatch(const char *name, bool silent = FALSE);
virtual				~BStopWatch();

		void		Suspend();
		void		Resume();
		bigtime_t	Lap();
		bigtime_t	ElapsedTime() const;
		void		Reset();
		const char	*Name() const;

private:

virtual	void		_ReservedStopWatch1();
virtual	void		_ReservedStopWatch2();

					BStopWatch(const BStopWatch &);
		BStopWatch	&operator=(const BStopWatch &);

		bigtime_t	fStart;
		bigtime_t	fSuspendTime;
		bigtime_t	fLaps[10];
		int32		fLap;
		const char	*fName;
		uint32		_reserved[2];
		bool		fSilent;
};

#endif
