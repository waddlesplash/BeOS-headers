//******************************************************************************
//
//	File:		Joystick.h
//
//	Description:	Joystick port class header.
//	
//	Copyright 1996, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_JOYSTICK_H
#define	_JOYSTICK_H

#ifndef SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifndef _OBJECT_H
#include <Object.h>
#endif

// -----------------------------------------------------------------------
class BJoystick : public BObject {

public:
				BJoystick();
virtual			~BJoystick();

long			Open(const char *portName);
void			Close(void);

long			Update(void);
double			timestamp;
short			horizontal;
short			vertical;
bool			button1;
bool			button2;

// -----------------------------------------------------------------------

private:

int				ffd;
};

#endif
