//******************************************************************************
//
//	File:		Joystick.h
//
//	Description:	Joystick port class header.
//	
//	Copyright 1996-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#pragma once

#ifndef	_JOYSTICK_H
#define	_JOYSTICK_H

#include <SupportDefs.h>

// -----------------------------------------------------------------------
class BJoystick {

public:
					BJoystick();
virtual				~BJoystick();

		status_t	Open(const char *portName);
		void		Close(void);

		status_t	Update(void);
		bigtime_t	timestamp;
		int16		horizontal;
		int16		vertical;
		bool		button1;
		bool		button2;

// -----------------------------------------------------------------------

private:

virtual	void		_ReservedJoystick1();
virtual	void		_ReservedJoystick2();
virtual	void		_ReservedJoystick3();

		int			ffd;
		uint32		_fReserved[3];
};

#endif
