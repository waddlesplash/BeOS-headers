//******************************************************************************
//
//	File:		DigitalPort.h
//
//	Description:	Digital Port class header.
//	
//	Copyright 1996-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#pragma once

#ifndef	_DIGITAL_PORT_H
#define	_DIGITAL_PORT_H

#include <stddef.h>
#include <SupportDefs.h>


// -----------------------------------------------------------------------
class BDigitalPort {

public:
					BDigitalPort();
virtual				~BDigitalPort();

		status_t	Open(const char *portName);
		void		Close(void);
		bool		IsOpen(void);

		ssize_t		Read(uint8 *buf);
		ssize_t		Write(uint8 value);

		status_t	SetAsOutput (void);
		bool		IsOutput (void);

		status_t	SetAsInput (void);
		bool		IsInput (void);


// -----------------------------------------------------------------------

private:

virtual	void		_ReservedDigitalPort1();
virtual	void		_ReservedDigitalPort2();
virtual	void		_ReservedDigitalPort3();

		int			ffd;
		bool		fIsInput;
		uint32		_fReserved[3];
};

#endif
