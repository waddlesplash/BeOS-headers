//******************************************************************************
//
//	File:		DigitalPort.h
//
//	Description:	Digital Port class header.
//	
//	Copyright 1996, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_DIGITAL_PORT_H
#define	_DIGITAL_PORT_H

#ifndef _OBJECT_H
#include <Object.h>
#endif

// -----------------------------------------------------------------------
class BDigitalPort : public BObject {

public:
				BDigitalPort();
virtual			~BDigitalPort();

long			Open(const char *portName);
void			Close(void);
bool			IsOpen(void);

long			Read(char *buf);
long			Write(char value);

long			SetAsOutput (void);
bool			IsOutput (void);

long			SetAsInput (void);
bool			IsInput (void);


// -----------------------------------------------------------------------

private:

int				ffd;
bool			fIsInput;
};

inline bool BDigitalPort::IsInput()
{
	return (fIsInput);
}

inline bool BDigitalPort::IsOutput()
{
	return (!fIsInput);
}

#endif
