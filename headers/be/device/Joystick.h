//******************************************************************************
//
//	File:		Joystick.h
//
//	Description:	Joystick port class header.
//	
//	Copyright 1996-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************


#ifndef	_JOYSTICK_H
#define	_JOYSTICK_H

#include <BeBuild.h>
#include <SupportDefs.h>
#include <OS.h>

class BList;

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

		int32		CountDevices();
		status_t	GetDeviceName(int32 n, char * name, 
						size_t bufSize = B_OS_NAME_LENGTH);

// -----------------------------------------------------------------------

private:

		void		ScanDevices();

virtual	void		_ReservedJoystick1();
virtual	void		_ReservedJoystick2();
virtual	void		_ReservedJoystick3();

		int			ffd;
		BList *		_fDevices;
		uint32		_fReserved[2];
};

#endif
