//******************************************************************************
//
//	File:		D2A.h
//
//	Description:	Digital-To-Analog converter class header.
//	
//	Copyright 1996, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_D2A_H
#define	_D2A_H

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifndef _OBJECT_H
#include <Object.h>
#endif

// -----------------------------------------------------------------------
class BD2A : public BObject {

public:
				BD2A();
virtual			~BD2A();

long			Open(const char *portName);
void			Close(void);
bool			IsOpen(void);

long			Read(uchar *buf);
long			Write(uchar value);

// -----------------------------------------------------------------------

private:

int				ffd;
};

#endif
